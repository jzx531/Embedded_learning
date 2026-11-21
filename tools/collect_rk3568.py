#!/usr/bin/env python3
"""Read-only board inventory. Run on the board; emit one JSON document on stdout."""
import base64
import datetime
import glob
import gzip
import json
import os
from pathlib import Path
import subprocess
import time


def read(path, binary=False):
    try:
        data = Path(path).read_bytes()
        return base64.b64encode(data).decode() if binary else data.decode(errors="replace")
    except Exception as exc:
        return {"error": str(exc)}


COMMANDS = {
    "identity": "id; date -Ins; uptime; uname -a; cat /etc/os-release; cat /etc/issue; hostnamectl; timedatectl",
    "cpu_memory": "lscpu; cat /proc/cpuinfo; free -b; cat /proc/meminfo; cat /proc/iomem; cat /proc/swaps",
    "boot": "cat /proc/cmdline; ls -la /boot; find /boot -maxdepth 3 -type f; cat /boot/extlinux/extlinux.conf; cat /etc/fstab; cat /proc/mounts",
    "storage": "lsblk -b -O; blkid; df -hT; cat /proc/partitions; cat /proc/mtd; ls -l /dev/disk/by-*",
    "network": "ip -details address show; ip route show table all; ip rule; cat /etc/resolv.conf; ls -l /etc/netplan; ss -lntup; for n in /sys/class/net/*; do echo INTERFACE:$n; cat $n/operstate $n/speed $n/duplex 2>/dev/null; ethtool ${n##*/} 2>/dev/null; ethtool -i ${n##*/} 2>/dev/null; done; iw dev; rfkill list",
    "usb_pci": "lsusb; lsusb -t; lspci -nnk; lspci -tv; usb-devices",
    "device_nodes": "ls -l /dev; cat /proc/devices; cat /proc/tty/driver/serial; cat /proc/tty/drivers; ls -l /dev/serial/by-*",
    "modules": "lsmod; cat /proc/modules; ls -la /lib/modules; find /lib/modules/$(uname -r) -maxdepth 2 -type f; cat /etc/modules; ls -l /etc/modules-load.d /etc/modprobe.d",
    "services": "systemctl --failed --no-pager; systemctl list-units --type=service --all --no-pager; systemctl list-unit-files --state=enabled --no-pager; systemctl get-default; ps -eo pid,comm,args; journalctl -b -p warning --no-pager -n 160",
    "software": "dpkg-query -W -f='${binary:Package}\t${Version}\n'; command -v gcc g++ make cmake python3 git dtc i2cdetect gpioinfo v4l2-ctl media-ctl aplay arecord bluetoothctl iw nmcli; python3 --version; gcc --version; cat /etc/apt/sources.list; ls -l /etc/apt/sources.list.d",
    "interrupts": "cat /proc/interrupts; cat /proc/softirqs; cat /proc/dma",
    "thermal_power": "for d in /sys/class/thermal/thermal_zone*; do echo ZONE:$d; cat $d/type $d/temp $d/trip_point* 2>/dev/null; done; for d in /sys/devices/system/cpu/cpufreq/policy*; do echo CPUFREQ:$d; cat $d/scaling_driver $d/scaling_governor $d/scaling_available_governors $d/scaling_available_frequencies $d/cpuinfo_min_freq $d/cpuinfo_max_freq $d/scaling_cur_freq 2>/dev/null; done; for d in /sys/class/devfreq/*; do echo DEVFREQ:$d; cat $d/name $d/governor $d/available_frequencies $d/cur_freq 2>/dev/null; done",
    "multimedia": "cat /proc/asound/cards /proc/asound/pcm /proc/asound/devices; aplay -l; arecord -l; v4l2-ctl --list-devices; ls -l /sys/class/drm; for d in /sys/class/drm/card*-*; do echo DRM:$d; cat $d/status $d/enabled $d/modes 2>/dev/null; done; ls -l /sys/class/video4linux /sys/class/media /sys/class/graphics; cat /proc/fb; ls -l /dev/mali* /dev/dri /dev/rga* /dev/mpp* /dev/rknpu*",
    "gpio_pwm_iio_input": "cat /sys/kernel/debug/gpio; cat /sys/kernel/debug/pwm; cat /proc/bus/input/devices; ls -l /sys/class/gpio /sys/class/pwm /sys/bus/iio/devices /sys/class/leds /sys/class/rtc /sys/class/watchdog; for d in /sys/class/rtc/rtc*; do echo RTC:$d; cat $d/name $d/date $d/time 2>/dev/null; done",
    "debug_summaries": "findmnt /sys/kernel/debug; cat /sys/kernel/debug/regulator/regulator_summary; cat /sys/kernel/debug/clk/clk_summary; cat /sys/kernel/debug/pm_genpd/pm_genpd_summary; cat /sys/kernel/debug/wakeup_sources; cat /sys/kernel/debug/dma_buf/bufinfo",
    "dmesg": "dmesg --color=never",
    "dt_sources": "ls -l /proc/device-tree /sys/firmware/fdt; find /boot /usr/lib /opt /home/kickpi -maxdepth 4 -type f \\( -name '*.dtb' -o -name '*.dtbo' -o -name '*.dts' -o -name '*.dtsi' \\) 2>/dev/null; ls -l /sys/kernel/config/device-tree/overlays; cat /etc/rc.local; ls -l /etc/profile.d; cat /home/kickpi/.bashrc /etc/profile",
}

result = {"collected_at": datetime.datetime.now(datetime.timezone.utc).isoformat(), "commands": {}, "files": {}, "buses": {}, "classes": {}, "device_tree": []}
for key, cmd in COMMANDS.items():
    started = time.monotonic()
    try:
        proc = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=35)
        item = {"command": cmd, "exit_code": proc.returncode, "output": proc.stdout.decode(errors="replace")}
    except subprocess.TimeoutExpired as exc:
        item = {"command": cmd, "error": "timeout", "output": (exc.stdout or b"").decode(errors="replace")}
    item["elapsed_seconds"] = round(time.monotonic() - started, 3)
    result["commands"][key] = item

for path in ["/sys/firmware/fdt", "/proc/config.gz"]:
    result["files"][path] = read(path, True)
for path in glob.glob("/sys/bus/mmc/devices/*/*"):
    if Path(path).is_file() and Path(path).name in {"name", "type", "cid", "csd", "date", "fwrev", "hwrev", "manfid", "oemid", "serial", "ocr", "erase_size", "preferred_erase_size", "life_time", "pre_eol_info"}:
        result["files"][path] = read(path)

base = Path("/sys/firmware/devicetree/base")
for current, dirs, files in os.walk(str(base)):
    dirs.sort()
    properties = {}
    for name in sorted(files):
        properties[name] = read(str(Path(current) / name), True)
    result["device_tree"].append({"path": "/" + str(Path(current).relative_to(base)).replace("\\", "/").strip("."), "properties": properties})

for bus in sorted(Path("/sys/bus").iterdir()):
    devices = []
    for dev in sorted((bus / "devices").glob("*")):
        item = {"name": dev.name, "sysfs_name": dev.name, "sysfs": str(dev.resolve())}
        for link in ["driver", "of_node", "iommu_group"]:
            target = dev / link
            if target.exists():
                item[link] = str(target.resolve())
        for name in ["uevent", "modalias", "name", "vendor", "device", "class", "irq", "resource", "status", "numa_node", "power/runtime_status"]:
            target = dev / name
            if target.is_file():
                item[name] = read(str(target))
        devices.append(item)
    if devices:
        result["buses"][bus.name] = devices

attrs = ["name", "dev", "uevent", "status", "enabled", "modes", "label", "ngpio", "base", "npwm", "type", "temp", "in_temp_input", "in_voltage_scale", "brightness", "max_brightness", "trigger", "identity", "state"]
for cls in sorted(Path("/sys/class").iterdir()):
    devices = []
    for dev in sorted(cls.glob("*")):
        item = {"name": dev.name, "sysfs_name": dev.name, "sysfs": str(dev.resolve())}
        for name in attrs:
            if (dev / name).is_file():
                item[name] = read(str(dev / name))
        devices.append(item)
    if devices:
        result["classes"][cls.name] = devices
print(json.dumps(result, ensure_ascii=True))
