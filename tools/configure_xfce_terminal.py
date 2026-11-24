"""Run as root on KICKPI to select the installed XFCE terminal, with backups."""
import datetime
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile


assert os.geteuid() == 0
terminal = "/usr/bin/xfce4-terminal.wrapper"
assert os.access(terminal, os.X_OK)
assert Path("/usr/share/xfce4/helpers/xfce4-terminal.desktop").is_file()
target = Path("/home/kickpi/.config/xfce4/helpers.rc")
backup = Path("/root/codex-terminal-" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S"))
backup.mkdir(mode=0o700)
previous = target.read_text() if target.exists() else ""
if target.exists():
    shutil.copy2(target, backup / "helpers.rc")
query = subprocess.check_output(
    ["update-alternatives", "--query", "x-terminal-emulator"], text=True)
(backup / "alternatives-before.txt").write_text(query)
(backup / "manifest.json").write_text(json.dumps({"helpers_existed": target.exists()}, indent=2))
lines = [line for line in previous.splitlines()
         if not line.startswith(("TerminalEmulator=", "TerminalEmulatorDismissed="))]
lines.extend(["TerminalEmulator=xfce4-terminal", "TerminalEmulatorDismissed=true"])
fd, temporary = tempfile.mkstemp(prefix=".terminal-", dir=target.parent)
try:
    with os.fdopen(fd, "w") as stream:
        stream.write("\n".join(lines).strip() + "\n")
    os.chown(temporary, 1000, 1000)
    os.chmod(temporary, 0o644)
    subprocess.run(["update-alternatives", "--set", "x-terminal-emulator", terminal],
                   check=True, timeout=10)
    os.replace(temporary, target)
finally:
    if os.path.exists(temporary):
        os.unlink(temporary)
print(json.dumps({"backup": str(backup), "xfce_helper": target.read_text(),
                  "system_terminal": str(Path("/usr/bin/x-terminal-emulator").resolve())}))
