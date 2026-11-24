"""Run as root on KICKPI: back up and switch only the local LightDM session."""
import configparser
import datetime
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile


def run(*args):
    return subprocess.check_output(args, text=True, stderr=subprocess.STDOUT,
                                   timeout=30).strip()


assert os.geteuid() == 0, "Root is required"
assert Path("/usr/share/xsessions/xfce.desktop").is_file()
assert os.access("/usr/bin/startxfce4", os.X_OK)
backup = Path("/root/codex-local-xfce-" + datetime.datetime.now().strftime("%Y%m%d-%H%M%S"))
backup.mkdir(mode=0o700)
override = Path("/etc/lightdm/lightdm.conf.d/99-local-xfce.conf")
dmrc = Path("/home/kickpi/.dmrc")
account = Path("/var/lib/AccountsService/users/kickpi")
targets = [override, dmrc, account]
account_args = ["org.freedesktop.Accounts", "/org/freedesktop/Accounts/User1000",
                "org.freedesktop.Accounts.User"]
old_sessions = {name: run("busctl", "get-property", *account_args, name)
                for name in ("Session", "XSession")}
manifest = {"files": {}, "account_properties": old_sessions}
for index, path in enumerate(targets):
    name = str(index) + "-" + path.name
    manifest["files"][str(path)] = name if path.exists() else None
    if path.exists():
        shutil.copy2(path, backup / name)
(backup / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")


def atomic_write(path, text, uid=0, gid=0, mode=0o644):
    fd, temporary = tempfile.mkstemp(prefix=".codex-", dir=path.parent)
    try:
        with os.fdopen(fd, "w") as stream:
            stream.write(text)
        os.chown(temporary, uid, gid)
        os.chmod(temporary, mode)
        os.replace(temporary, path)
    finally:
        if os.path.exists(temporary):
            os.unlink(temporary)


try:
    atomic_write(override, "[Seat:*]\nuser-session=xfce\nautologin-session=xfce\n")
    config = configparser.ConfigParser(interpolation=None)
    config.optionxform = str
    config.read(dmrc)
    if not config.has_section("Desktop"):
        config.add_section("Desktop")
    config["Desktop"]["Session"] = "xfce"
    contents = io.StringIO()
    config.write(contents, space_around_delimiters=False)
    atomic_write(dmrc, contents.getvalue(), uid=1000, gid=1000, mode=0o644)
    for method in ("SetSession", "SetXSession"):
        run("busctl", "call", *account_args, method, "s", "xfce")
    effective = run("lightdm", "--show-config")
    (backup / "lightdm-effective-after.txt").write_text(effective + "\n")
    print(json.dumps({"backup": str(backup), "lightdm_config": effective}), flush=True)
except Exception:
    for path_string, saved_name in manifest["files"].items():
        path = Path(path_string)
        if saved_name is None:
            if path.exists():
                path.unlink()
        else:
            saved = backup / saved_name
            shutil.copy2(saved, path)
            if path == dmrc:
                os.chown(path, 1000, 1000)
    for name, value in old_sessions.items():
        import shlex
        run("busctl", "call", *account_args, "Set" + name, "s", shlex.split(value)[1])
    raise

run("systemctl", "restart", "lightdm")
print("Local LightDM restarted; verify the XFCE session before reporting success.")
