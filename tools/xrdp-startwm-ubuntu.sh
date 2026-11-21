#!/bin/sh
# Ubuntu GNOME session for xrdp. Keep the DISPLAY supplied by sesman.
unset DBUS_SESSION_BUS_ADDRESS SESSION_MANAGER WAYLAND_DISPLAY
unset COGL_DRIVER LD_PRELOAD
export XDG_SESSION_TYPE=x11
export XDG_SESSION_DESKTOP=ubuntu
export XDG_CURRENT_DESKTOP=ubuntu:GNOME
export GNOME_SHELL_SESSION_MODE=ubuntu
export XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
export XDG_DATA_DIRS=/usr/share/ubuntu:/usr/local/share:/usr/share:/var/lib/snapd/desktop
# Virtual xrdp displays have no physical Mali scanout device.
export LIBGL_ALWAYS_SOFTWARE=1
export GALLIUM_DRIVER=llvmpipe
export __GLX_VENDOR_LIBRARY_NAME=mesa
export __EGL_VENDOR_LIBRARY_FILENAMES=/usr/share/glvnd/egl_vendor.d/50_mesa.json
exec dbus-run-session -- /usr/bin/gnome-session --session=ubuntu
