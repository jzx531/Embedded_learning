#!/usr/bin/env python3
"""Temporary xrdp Xorg/GNOME check. Run as root; clean up spawned groups only."""
import json
import os
from pathlib import Path
import pwd
import signal
import subprocess
import tempfile
import time

user = pwd.getpwnam("kickpi")
number = next(n for n in range(20, 30) if not Path(f"/tmp/.X11-unix/X{n}").exists() and not Path(f"/tmp/.X{n}-lock").exists())
display = f":{number}"
folder = Path(tempfile.mkdtemp(prefix="gnome-rdp-check-"))
os.chown(folder, user.pw_uid, user.pw_gid)
auth = folder / "Xauthority"
auth.touch(mode=0o600)
os.chown(auth, user.pw_uid, user.pw_gid)
cookie = subprocess.check_output(["mcookie"], text=True).strip()
subprocess.run(["runuser", "-u", user.pw_name, "--", "xauth", "-f", str(auth), "add", display, ".", cookie], check=True)
env = dict(HOME=user.pw_dir, USER=user.pw_name, LOGNAME=user.pw_name,
           PATH="/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin", LANG="en_US.UTF-8",
           DISPLAY=display, XAUTHORITY=str(auth),
           XDG_RUNTIME_DIR=f"/run/user/{user.pw_uid}", XDG_SESSION_TYPE="x11",
           LIBGL_ALWAYS_SOFTWARE="1", GALLIUM_DRIVER="llvmpipe")
processes = []
report = dict(directory=str(folder), display=display)

def become_user():
    os.initgroups(user.pw_name, user.pw_gid)
    os.setgid(user.pw_gid)
    os.setuid(user.pw_uid)

def check(*args, timeout=5):
    try:
        p = subprocess.run(args, env=env, cwd=user.pw_dir, preexec_fn=become_user,
                           capture_output=True, timeout=timeout)
        return dict(code=p.returncode, output=(p.stdout + p.stderr).decode(errors="replace"))
    except subprocess.TimeoutExpired:
        return dict(error="timeout")

def spawn(args, log):
    with (folder / log).open("wb") as out:
        p = subprocess.Popen(args, env=env, cwd=user.pw_dir, preexec_fn=become_user,
                             stdout=out, stderr=out, start_new_session=True)
    processes.append(p)
    return p

try:
    xorg = spawn(["/usr/lib/xorg/Xorg", display, "-auth", str(auth), "-config",
                  "xrdp/xorg.conf", "-configdir", "xrdp/conf.d", "-noreset", "-nolisten", "tcp",
                  "-logfile", str(folder / "Xorg.log")], "xorg-console.log")
    for attempt in range(15):
        time.sleep(1)
        if check("xdpyinfo", timeout=2).get("code") == 0:
            report["xorg_ready"] = True
            break
        if xorg.poll() is not None:
            break
    if report.get("xorg_ready"):
        report["glx"] = check("glxinfo", "-B", timeout=10)
        desktop = spawn(["/home/kickpi/startwm.sh"], "desktop.log")
        time.sleep(30)
        report["desktop_exit"] = desktop.poll()
        report["root_properties"] = check("xprop", "-root", "_NET_SUPPORTING_WM_CHECK", "_NET_CLIENT_LIST")
        report["windows"] = check("xwininfo", "-root", "-tree")
    report["xorg_exit"] = xorg.poll()
finally:
    for p in reversed(processes):
        if p.poll() is None:
            os.killpg(p.pid, signal.SIGTERM)
            try:
                p.wait(timeout=5)
            except subprocess.TimeoutExpired:
                os.killpg(p.pid, signal.SIGKILL)
                p.wait(timeout=3)
    for name in ("Xorg.log", "desktop.log", "xorg-console.log"):
        if (folder / name).exists():
            report[name] = (folder / name).read_text(errors="replace")[-20000:]
    (folder / "result.json").write_text(json.dumps(report, indent=2))
print(json.dumps(report))
