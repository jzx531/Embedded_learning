#!/bin/sh
# xrdp-sesman calls this per-user override with DISPLAY=:10, :11, ... .
# The vendor /etc/profile.d/display.sh forces DISPLAY=:0.0, so do not source
# the login profile here. Keep the physical desktop and RDP session separate.
if [ -z "${DISPLAY:-}" ]; then
    echo 'xrdp: DISPLAY is not set; refusing to start a desktop' >&2
    exit 1
fi

if [ -r /etc/default/locale ]; then
    . /etc/default/locale
    export LANG
fi

unset SESSION_MANAGER DBUS_SESSION_BUS_ADDRESS
exec /usr/bin/dbus-run-session -- /usr/bin/xfce4-session
