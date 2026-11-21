#!/usr/bin/env python3
"""Export captured evidence and lossless, numeric-phandle DTS without dependencies."""
import base64
from collections import Counter
import gzip
import hashlib
import json
from pathlib import Path
import re
import struct

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "rk3568-data"
OUT.mkdir(exist_ok=True)
data = json.loads((ROOT / "rk3568-inventory.json").read_text(encoding="utf-8-sig"))


def emit(name, value):
    if isinstance(value, bytes):
        (OUT / name).write_bytes(value)
    else:
        (OUT / name).write_text(value, encoding="utf-8", newline="\n")


def text_prop(props, name, default=""):
    raw = props.get(name)
    if raw is None:
        return default
    return raw.rstrip(b"\0").decode("utf-8", errors="replace").replace("\0", ", ")


def value_dts(value):
    if not value:
        return ""
    if value.endswith(b"\0") and all(c == 0 or 32 <= c < 127 for c in value) and value != b"\0" * len(value):
        rendered = ", ".join(json.dumps(s.decode("ascii")) for s in value[:-1].split(b"\0"))
        recovered = b"".join(json.loads(s).encode("ascii") + b"\0" for s in re.findall(r'"(?:\\.|[^"\\])*"', rendered))
    elif len(value) % 4 == 0:
        cells = struct.unpack(">" + "I" * (len(value) // 4), value)
        rendered = "<" + " ".join("0x%x" % c for c in cells) + ">"
        recovered = b"".join(struct.pack(">I", int(c, 16)) for c in rendered[1:-1].split())
    else:
        rendered = "[" + " ".join("%02x" % c for c in value) + "]"
        recovered = bytes.fromhex(rendered[1:-1])
    assert recovered == value, "DTS property byte roundtrip failed"
    return " = " + rendered


live = {n["path"]: {k: base64.b64decode(v) for k, v in n["properties"].items()} for n in data["device_tree"]}
blob = base64.b64decode(data["files"]["/sys/firmware/fdt"])
header = struct.unpack_from(">10I", blob)
magic, total, off_struct, off_strings, off_reserve, version, last_version, boot_cpu, size_strings, size_struct = header
assert magic == 0xD00DFEED and total == len(blob)
assert off_struct + size_struct <= total and off_strings + size_strings <= total
strings = blob[off_strings:off_strings + size_strings]
nodes = {}
stack = []
pos = off_struct
while pos < off_struct + size_struct:
    token = struct.unpack_from(">I", blob, pos)[0]
    pos += 4
    if token == 1:
        end = blob.index(b"\0", pos)
        name = blob[pos:end].decode("ascii")
        stack.append(name)
        path = "/" + "/".join(stack[1:])
        assert path not in nodes
        nodes[path] = {}
        pos = (end + 4) & ~3
    elif token == 2:
        stack.pop()
    elif token == 3:
        length, offset = struct.unpack_from(">II", blob, pos)
        pos += 8
        name = strings[offset:strings.index(b"\0", offset)].decode("ascii")
        nodes["/" + "/".join(stack[1:])][name] = blob[pos:pos + length]
        pos = (pos + length + 3) & ~3
    elif token == 4:
        pass
    elif token == 9:
        assert not stack
        break
    else:
        raise ValueError("Invalid FDT token %s" % token)
else:
    raise ValueError("Missing FDT_END")
reservations = []
pos = off_reserve
while True:
    address, size = struct.unpack_from(">QQ", blob, pos)
    pos += 16
    if not address and not size:
        break
    reservations.append((address, size))


def dts(tree, reserves=()):
    children = {}
    for path in tree:
        if path != "/":
            children.setdefault(path.rsplit("/", 1)[0] or "/", []).append(path)
    lines = ["/dts-v1/;", "", "// Exported from captured runtime data; phandles are numeric."]
    for addr, size in reserves:
        lines.append("/memreserve/ 0x%x 0x%x;" % (addr, size))

    def walk(path, level):
        indent = "\t" * level
        lines.append(indent + ("/" if path == "/" else path.rsplit("/", 1)[1]) + " {")
        for name, value in tree[path].items():
            lines.append(indent + "\t" + name + value_dts(value) + ";")
        for child in children.get(path, []):
            walk(child, level + 1)
        lines.append(indent + "};")

    walk("/", 0)
    return "\n".join(lines) + "\n"


emit("runtime-fdt.dtb", blob)
emit("runtime-fdt.dts", dts(nodes, reservations))
emit("live-tree.dts", dts(live))
emit("kernel.config", gzip.decompress(base64.b64decode(data["files"]["/proc/config.gz"])))
for name, item in data["commands"].items():
    emit(name + ".txt", "$ " + item["command"] + "\n\n" + item.get("output", "") + "\n\n[collector exit_code=%s; error=%s; seconds=%s]\n" % (item.get("exit_code"), item.get("error", ""), item["elapsed_seconds"]))

drivers = {}
for bus, devices in data["buses"].items():
    for device in devices:
        path = device.get("of_node", "").removeprefix("/sys/firmware/devicetree/base") or "/"
        if device.get("of_node"):
            drivers.setdefault(path, []).append(bus + ":" + Path(device["sysfs"]).name + (" -> " + device["driver"].rsplit("/", 1)[-1] if device.get("driver") else " (no driver link)"))


def effective_status(path):
    chain = []
    while True:
        chain.append(path)
        if path == "/":
            break
        path = path.rsplit("/", 1)[0] or "/"
    for ancestor in reversed(chain):
        state = text_prop(live.get(ancestor, {}), "status", "okay (implicit)")
        if state not in {"okay", "ok", "okay (implicit)"}:
            return state + " @ " + ancestor
    return "okay"


def cell(value):
    return str(value).replace("|", "\\|").replace("\n", "<br>")


lines = ["# RK3568 运行时设备树与设备完整索引", "", "数据来源：`rk3568-inventory.json`。节点未写 status 时按规范解释为 okay；父节点禁用会使子节点不可用。okay 只表示配置允许，驱动链接及启动日志才反映枚举/探测情况。", "", "## 设备树全部节点", "", "| 节点路径 | compatible | 本节点 status | 按祖先判断的 status | sysfs 设备 / 驱动 |", "|---|---|---|---|---|"]
for path, props in live.items():
    lines.append("| " + " | ".join(cell(v) for v in [path, text_prop(props, "compatible"), text_prop(props, "status", "未声明"), effective_status(path), "; ".join(drivers.get(path, []))]) + " |")
lines += ["", "## 全部已枚举总线设备", ""]
for bus, devices in data["buses"].items():
    lines += ["### " + bus + " (%d)" % len(devices), "", "| 设备名 | 绑定驱动 | 设备树节点 | sysfs 路径 |", "|---|---|---|---|"]
    for dev in devices:
        lines.append("| " + " | ".join(cell(v) for v in [Path(dev["sysfs"]).name, dev.get("driver", "无 driver 链接"), dev.get("of_node", ""), dev["sysfs"]]) + " |")
    lines.append("")
lines += ["## 全部 sysfs class 设备", ""]
for cls, devices in data["classes"].items():
    lines += ["### " + cls + " (%d)" % len(devices), "", "| 设备名 | 名称 / 备注 | sysfs 路径 |", "|---|---|---|"]
    for dev in devices:
        lines.append("| " + " | ".join(cell(v) for v in [Path(dev["sysfs"]).name, dev.get("identity", dev.get("label", dev.get("name", ""))), dev["sysfs"]]) + " |")
    lines.append("")
emit("device-index.md", "\n".join(lines) + "\n")

changes = []
for path in sorted(set(live) | set(nodes)):
    for key in sorted(set(live.get(path, {})) | set(nodes.get(path, {}))):
        old, new = nodes.get(path, {}).get(key), live.get(path, {}).get(key)
        if old != new:
            changes.append({"path": path, "property": key, "fdt_hex": old.hex() if old is not None else None, "live_hex": new.hex() if new is not None else None})
summary = {"collected_at": data["collected_at"], "fdt_bytes": len(blob), "fdt_version": version, "fdt_nodes": len(nodes), "live_nodes": len(live), "fdt_properties": sum(map(len, nodes.values())), "live_properties": sum(map(len, live.values())), "property_encoding_roundtrip": "all properties preserved", "fdt_live_differences": changes, "effective_status_counts": dict(Counter(effective_status(p).split(" @ ")[0] for p in live)), "bus_counts": {k: len(v) for k, v in data["buses"].items()}, "class_counts": {k: len(v) for k, v in data["classes"].items()}, "commands_with_timeout": [k for k,v in data["commands"].items() if v.get("error")]}
emit("validation.json", json.dumps(summary, ensure_ascii=False, indent=2) + "\n")
extra_path = OUT / "extra.json"
if extra_path.exists():
    extra = json.loads(extra_path.read_text(encoding="utf-8-sig"))
    for name, item in extra["commands"].items():
        emit("extra-" + name + ".txt", "$ " + item["command"] + "\n\n" + item["output"])
key_nodes = []
for path, props in nodes.items():
    if path == "/" or path in {"/aliases", "/chosen", "/fiq-debugger", "/dmc"} or re.match(r"^/(serial@|i2c@|spi@|pcie@|can@|dwmmc@|sdhci@|wireless-|backlight|leds|adc-keys|reserved-memory)", path) or "/display-timings/" in path:
        key_nodes.append(path)
        for name, value in props.items():
            key_nodes.append("  " + name + (value_dts(value) if len(value) < 220 else " = [omitted here; %d bytes; see full DTS]" % len(value)) + ";")
emit("key-nodes.txt", "\n".join(key_nodes) + "\n")
hashes = []
for path in sorted(OUT.iterdir()):
    if path.is_file() and path.name != "SHA256SUMS.txt":
        hashes.append(hashlib.sha256(path.read_bytes()).hexdigest() + "  " + path.name)
hashes.append(hashlib.sha256((ROOT / "rk3568-inventory.json").read_bytes()).hexdigest() + "  ../rk3568-inventory.json")
emit("SHA256SUMS.txt", "\n".join(hashes) + "\n")
compact = {k: v for k, v in summary.items() if k not in {"fdt_live_differences", "class_counts"}}
compact["fdt_live_difference_properties"] = dict(Counter(x["property"] for x in changes))
print(json.dumps(compact, ensure_ascii=True, indent=2))
