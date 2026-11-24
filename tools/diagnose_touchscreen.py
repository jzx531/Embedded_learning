"""Run read-only SSH diagnostics against the previously verified KICKPI host key."""
import argparse
import base64
import getpass
import json
import os
from pathlib import Path
import shlex
import sys

import paramiko


parser = argparse.ArgumentParser()
parser.add_argument("--host", default="192.168.3.181")
source = parser.add_mutually_exclusive_group(required=True)
source.add_argument("--command")
source.add_argument("--script", help="Local Python source to execute on the board")
parser.add_argument("--sudo", action="store_true")
args = parser.parse_args()

client = paramiko.SSHClient()
key = paramiko.Ed25519Key(data=base64.b64decode(
    "AAAAC3NzaC1lZDI1NTE5AAAAIHtvSjSu3Twt4bCjgzcLy2fEbrklVzQUmqQ3wCoxotXJ"))
client.get_host_keys().add(args.host, "ssh-ed25519", key)
client.set_missing_host_key_policy(paramiko.RejectPolicy())
try:
    password = os.environ.get("KICKPI_SSH_PASSWORD") or getpass.getpass()
    client.connect(args.host, username="kickpi",
                   password=password,
                   look_for_keys=False, allow_agent=False, timeout=8,
                   auth_timeout=10, banner_timeout=10)
    command = args.command
    if args.script:
        command = "python3 -c " + shlex.quote(Path(args.script).read_text(encoding="utf-8"))
    if args.sudo:
        command = "sudo -S -p '' -- sh -c " + shlex.quote(command)
    stdin, stdout, stderr = client.exec_command(command, timeout=65)
    if args.sudo:
        stdin.write(password + "\n")
        stdin.flush()
    stdin.close()
    result = {"host": args.host, "stdout": stdout.read().decode(errors="replace"),
              "stderr": stderr.read().decode(errors="replace"),
              "exit_code": stdout.channel.recv_exit_status()}
    sys.stdout.reconfigure(encoding="utf-8")
    print(json.dumps(result, ensure_ascii=False, indent=2))
finally:
    client.close()
