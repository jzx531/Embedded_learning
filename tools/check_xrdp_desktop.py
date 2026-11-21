#!/usr/bin/env python3
"""Root-only temporary Xorg/XFCE check; stop only processes created by this check."""
import json
import os
from pathlib import Path
import pwd
import signal
import subprocess
import sys
import tempfile
import time

account = pwd.getpwnam("kickpi")
display_number = next(n for n in range(20, 30) if not Path("/tmp/.X11-unix/X%d" % n).exists() and not Path("/tmp/.X%d-lock" % n).exists())
display = ":%d" % display_number
folder = Path(tempfile.mkdtemp(prefix="xrdp-check-", dir="/tmp"))
os.chown(str(folder), account.pw_uid, account.pw_gid)
auth = folder / "Xauthority"
auth.touch(mode=0o600)
os.chown(str(auth), account.pw_uid, account.pw_gid)
cookie = subprocess.check_output(["mcookie"], text=True).strip()
subprocess.run(["runuser", "-u", "kickpi", "--", "xauth", "-f", str(auth), "add", display, ".", cookie], check=True)
env = {"HOME": account.pw_dir, "USER": "kickpi", "LOGNAME": "kickpi", "PATH": "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", "DISPLAY": display, "XAUTHORITY": str(auth), "XDG_RUNTIME_DIR": "/run/user/1001", "LANG": "en_US.UTF-8", "XRDP_SESSION": "1", "XDG_SESSION_TYPE": "x11"}
prefix = ["runuser", "-u", "kickpi", "--", "env", "-i"] + [k + "=" + v for k, v in env.items()]
processes = []
report = {"temporary_directory": str(folder), "display": display}


def check(*cmd, timeout=3):
    p = subprocess.run(prefix + list(cmd), stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=timeout)
    return {"exit_code": p.returncode, "output": p.stdout.decode(errors="replace")}


def become_user():
    os.setgroups([])
    os.setgid(account.pw_gid)
    os.setuid(account.pw_uid)


try:
    with (folder / "xorg-console.log").open("wb") as log:
        xorg = subprocess.Popen(["/usr/lib/xorg/Xorg", display, "-auth", str(auth), "-config", sys.argv[1] if len(sys.argv) > 1 else "xrdp/xorg.conf", "-noreset", "-nolisten", "tcp", "-logfile", str(folder / "Xorg.log")], env=env, cwd=account.pw_dir, preexec_fn=become_user, stdout=log, stderr=log, start_new_session=True)
    processes.append(xorg)
    ready = False
    for attempt in range(12):
        time.sleep(1)
        try:
            result = check("xdpyinfo")
            if result["exit_code"] == 0:
                ready = True
                report["xorg_ready"] = True
                break
        except subprocess.TimeoutExpired:
            pass
        if xorg.poll() is not None:
            break
    if ready:
        with (folder / "desktop.log").open("wb") as log:
            desktop = subprocess.Popen(["/home/kickpi/startwm.sh"], env=env, cwd=account.pw_dir, preexec_fn=become_user, stdout=log, stderr=log, start_new_session=True)
        processes.append(desktop)
        time.sleep(10)
        report["desktop_exit_code"] = desktop.poll()
        report["root_properties"] = check("xprop", "-root", "_NET_SUPPORTING_WM_CHECK", "_NET_CLIENT_LIST")
        report["window_tree"] = check("xwininfo", "-root", "-tree")
    else:
        report["xorg_ready"] = False
        report["xorg_exit_code"] = xorg.poll()
finally:
    for process in reversed(processes):
        if process.poll() is None:
            os.killpg(process.pid, signal.SIGTERM)
            try:
                process.wait(timeout=5)
            except subprocess.TimeoutExpired:
                os.killpg(process.pid, signal.SIGKILL)
                process.wait(timeout=3)
    for name in ["Xorg.log", "desktop.log", "xorg-console.log"]:
        path = folder / name
        if path.exists():
            report[name] = path.read_text(errors="replace")[-18000:]
    (folder / "result.json").write_text(json.dumps(report, indent=2))
print(json.dumps(report))
