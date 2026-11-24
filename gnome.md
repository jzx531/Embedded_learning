# RK3568 KICKPI：Ubuntu GNOME 桌面移植与 RDP 配置全过程

> **2026-11-23 更新：** 为排查板载 DSI 触摸响应卡顿，已按用户要求将本地自动登录会话切换到已有 XFCE；GNOME 软件和 RDP 的 GNOME 启动配置保留。当前本地屏幕为 800×1280。下文前十二节保留此前 GNOME 部署的历史过程，最新切换记录见第 13 节。

记录日期：2026-11-21（Asia/Shanghai）。本文整理本次 SSH 实机操作、故障排查、最终配置和验证结果；最后一次核对约为当日 23:24。登录目标为 `kickpi@192.168.3.181`，管理操作通过 sudo 完成，本文不保存密码。

当前结果：用户已确认 **HDMI 桌面尺寸正常、鼠标点击正常、键盘可以输入**；LightDM、xrdp、xrdp-sesman 均为 active。HDMI 当前桌面为 **2560×1440**。分辨率是本次运行中通过 framebuffer ioctl 调整的，**尚未配置开机自动恢复，也未验证整板重启后的结果**。

## 1. 目标、系统版本与实施范围

用户希望将板厂桌面改为“Ubuntu 22.04 默认的经典桌面”，并安装 Windows 可连接的 RDP 服务。本次按 Ubuntu 默认的 GNOME 布局实现：顶部状态栏、左侧 Ubuntu Dock、Yaru 主题、桌面图标、Nautilus 文件管理器及 GNOME Terminal。

这里的“经典桌面”指用户期望的 Ubuntu 默认外观；实际会话为 `ubuntu-xorg` / Ubuntu GNOME，并非 GNOME Classic 会话，也没有将系统降级为 Ubuntu 22.04。

| 项目 | 本次实机信息 |
|---|---|
| 设备树型号 | Rockchip RK3568 KICKPI K1Mini Board |
| SSH 地址 | `192.168.3.181` |
| 用户 / UID / GID | `kickpi` / `1000` / `1000` |
| 发行版 | Ubuntu 24.04.4 LTS，noble，arm64 |
| 内核 | `6.1.141 #4 SMP Wed Sep 2 15:59:40 CST 2026 aarch64` |
| 镜像构建信息 | `root@kickpi Fri Sep 11 10:44:40 CST 2026` |
| 内存 | 约 3.8 GiB，无 swap |
| 安装后根分区 | 29 GiB，总使用约 6.4 GiB，可用约 21 GiB |
| 原桌面 | XFCE，LightDM 自动登录 |
| 新桌面 | GNOME 46，Ubuntu session，Xorg |
| 显示管理器 | 继续使用 LightDM |

因此，镜像文件名中的 `ubuntu2404` 与当前系统信息一致。Ubuntu 22.04 通常使用 GNOME 42，本机安装的是与 Ubuntu 24.04 软件源配套的 GNOME 46。工作内容属于桌面会话、显示兼容和远程桌面配置，没有编译 GNOME、替换内核、修改设备树或重刷镜像。

原先 `10.203.155.1`、K1A、Ubuntu 20.04 / Linux 5.10 的采集保存在 [Rk3568.md](Rk3568.md)，是另一份历史系统快照，不能与本次版本混用。

## 2. 最终图形方案

| 链路 | 启动和显示路径 | 渲染方式 |
|---|---|---|
| HDMI 本地桌面 | LightDM → 本地 Xorg → `fbdev` → `/dev/fb0` → Ubuntu GNOME | GNOME Shell 强制 Mesa llvmpipe 软件渲染 |
| Windows RDP | TCP 3389 → xrdp → sesman → 独立 Xorg / `xorgxrdp` → Ubuntu GNOME | 独立 D-Bus，会话环境强制 Mesa llvmpipe |

RDP 创建独立桌面，不是 HDMI 画面的镜像。初次部署已经验证同一 kickpi 账户的本地与远程 GNOME 可以同时运行。

板厂 Mali EGL 与本地 GNOME 的组合出现黑屏；随后发现，单独替换 GNOME 的 EGL 路径仍不足以解决本地画面更新问题。因此最终同时保留 GNOME 的 Mesa 覆盖配置，并把本地 Xorg 从板厂 modesetting/glamor 路径切换到 fbdev。

这是一套以当前实机可操作为目标的兼容配置，并未实现 GNOME 的 Mali GPU 硬件加速。fbdev 仍使用内核已有 framebuffer，未卸载 Rockchip 内核显示驱动。

## 3. 安装前检查与备份

先确认发行版、架构、内核、显示管理器、会话及软件包状态，再安装匹配当前发行版的软件。板端保留的原始备份目录为：

```text
/root/codex-gnome-rdp-backup/
├── holds-before.txt                 原始 hold 清单
├── packages-before.txt              安装前包版本
├── holds-restored.log               恢复 hold 的记录
├── install.log                      主安装日志
├── lightdm/                         原 LightDM 配置
├── xorg.conf.d/                     原本地 Xorg 配置
├── 20-modesetting.before-click-fix.conf
├── kickpi                           原 AccountsService 用户记录
├── onboard.desktop                  原屏幕键盘自启动项
├── gnome-dconf-before.ini            原 GNOME 设置导出
├── xrdp/                            原 xrdp / Xorg 配置备份
├── remote-desktop-check*.json        初期图形诊断记录
├── rdp-client-test.log               真实 RDP 连接测试
└── test-client-install.log           测试客户端安装日志
```

备份目录为 root 专用。下面命令可用于重新核查系统，不会切换桌面：

```sh
cat /etc/os-release
uname -a
tr '\0' '\n' < /proc/device-tree/model
systemctl status lightdm --no-pager
lightdm --show-config
apt-mark showhold | wc -l
dpkg --audit
```

本镜像原有 **2348 个 hold 包**。本次先模拟依赖变更，仅允许完成桌面安装所需的依赖更新，安装后恢复原 hold 清单。主安装事务为 **25 个包升级、95 个新包、0 个删除**；另外安装了真实 RDP 验证所需的 FreeRDP 客户端及客户端库。未执行全系统 upgrade、全量 unhold 或 autoremove，也没有替换板厂内核。

## 4. 安装 GNOME 与 RDP 软件

使用镜像已有的 USTC Ubuntu Ports 软件源。核心安装命令如下；它表达安装目标，不是包含所有模拟检查和定向解锁步骤的一键脚本：

```sh
sudo apt-get update
sudo apt-get install --no-install-recommends \
  ubuntu-desktop-minimal xrdp xorgxrdp dbus-x11 \
  gnome-terminal yaru-theme-gtk yaru-theme-icon \
  xdg-desktop-portal-gnome
```

对于同类板厂镜像，应先保存 `apt-mark showhold`、模拟安装并核对升级/删除清单，再按依赖处理锁定包；不要直接解除全部锁定。完整事务输出在板端 `install.log`，本文不将一般安装命令冒充当时完整终端逐行记录。

GDM3 随依赖安装，但实际显示管理器仍选用 LightDM，保留板厂已有的自动登录机制。主要版本如下：

| 软件 | 已安装版本 |
|---|---|
| ubuntu-desktop-minimal | `1.539.2` |
| ubuntu-session | `46.0-1ubuntu4` |
| gnome-shell | `46.0-0ubuntu6~24.04.17` |
| gnome-shell-extension-ubuntu-dock | `90ubuntu3` |
| gnome-terminal | `3.52.0-1ubuntu2` |
| xrdp | `0.9.24-4ubuntu0.1` |
| xorgxrdp | `1:0.9.19-1` |

## 5. 将本地默认会话切换到 Ubuntu GNOME

新增 `/etc/lightdm/lightdm.conf.d/90-ubuntu-gnome.conf`：

```ini
[Seat:*]
user-session=ubuntu-xorg
autologin-session=ubuntu-xorg
```

原有 `/etc/lightdm/lightdm.conf.d/50-myconfig.conf` 中的 kickpi 自动登录设置继续生效。`/home/kickpi/.dmrc` 为：

```ini
[Desktop]
Session=ubuntu-xorg
```

`/var/lib/AccountsService/users/kickpi` 中 `[User]` 段的 `Session` 和 `XSession` 同步设为 `ubuntu-xorg`，保留其余用户属性。

在 kickpi 用户的图形会话 D-Bus 下配置外观，最终值如下：

```sh
gsettings set org.gnome.desktop.interface gtk-theme 'Yaru'
gsettings set org.gnome.desktop.interface icon-theme 'Yaru'
gsettings set org.gnome.desktop.interface cursor-theme 'Yaru'
gsettings set org.gnome.desktop.interface enable-animations false
gsettings set org.gnome.shell.extensions.dash-to-dock dock-position 'LEFT'
gsettings set org.gnome.shell.extensions.dash-to-dock extend-height true
gsettings set org.gnome.shell favorite-apps \
  "['org.gnome.Nautilus.desktop', 'org.gnome.Terminal.desktop', 'org.gnome.Settings.desktop']"
```

从 root SSH shell 调用时，用以下前缀连接 kickpi 的用户会话，再接具体的 `gsettings` 命令，避免写入 root 的设置：

```sh
runuser -u kickpi -- env \
  XDG_RUNTIME_DIR=/run/user/1000 \
  DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus \
  gsettings get org.gnome.desktop.interface gtk-theme
```

原有 `/home/kickpi/.config/autostart/onboard.desktop` 增加 `NotShowIn=GNOME;`，避免 GNOME 登录后持续弹出屏幕键盘。原 XFCE 软件包和用户配置保留。

修改后通过重启 LightDM 进入新会话。重启 LightDM 会结束本地桌面和未保存的应用，本次排障中实际执行过多次，没有为最终配置额外重启整块开发板。

## 6. 配置 xrdp 的 Ubuntu GNOME 会话

### 6.1 用户启动脚本

部署 `/home/kickpi/startwm.sh`，属主 `kickpi:kickpi`、权限 `0755`。对应仓库文件为 [tools/xrdp-startwm-ubuntu.sh](tools/xrdp-startwm-ubuntu.sh)。内容如下：

```sh
#!/bin/sh
unset DBUS_SESSION_BUS_ADDRESS SESSION_MANAGER WAYLAND_DISPLAY
unset COGL_DRIVER LD_PRELOAD
export XDG_SESSION_TYPE=x11
export XDG_SESSION_DESKTOP=ubuntu
export XDG_CURRENT_DESKTOP=ubuntu:GNOME
export GNOME_SHELL_SESSION_MODE=ubuntu
export XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg
export XDG_DATA_DIRS=/usr/share/ubuntu:/usr/local/share:/usr/share:/var/lib/snapd/desktop
export LIBGL_ALWAYS_SOFTWARE=1
export GALLIUM_DRIVER=llvmpipe
export __GLX_VENDOR_LIBRARY_NAME=mesa
export __EGL_VENDOR_LIBRARY_FILENAMES=/usr/share/glvnd/egl_vendor.d/50_mesa.json
exec dbus-run-session -- /usr/bin/gnome-session --session=ubuntu
```

`sesman.ini` 的 `EnableUserWindowManager=true` 使 kickpi 登录时调用此脚本。脚本保留 sesman 分配的 `DISPLAY`，不能强行设为本地 `:0`。清理旧 D-Bus 环境并建立独立 bus，是为了让远程会话与本地会话分别启动；Mesa 环境用于避免远程虚拟显示误用实体 Mali 显示路径。

### 6.2 隔离远程和本地 Xorg 配置

初期测试发现，远程 Xorg 会共同读取 `/etc/X11/xorg.conf.d/20-modesetting.conf` 中的板厂 Screen/Device 配置，日志出现 `Cannot open /dev/tty0 (Permission denied)`。

解决方法是为远程 Xorg 新建空片段目录 `/etc/X11/xrdp/conf.d/`，并把 `/etc/xrdp/sesman.ini` 的 `[Xorg]` 段配置为：

```ini
[Xorg]
param=/usr/lib/xorg/Xorg
param=-config
param=xrdp/xorg.conf
param=-configdir
param=xrdp/conf.d
param=-noreset
param=-nolisten
param=tcp
param=-logfile
param=.xorgxrdp.%s.log
```

`/etc/X11/xrdp/xorg.conf` 保留 xorgxrdp 的 ServerLayout、输入设备、模块及 Screen 配置，并修改以下关键项：

```xorg
# 位于现有 ServerFlags 段中
Option "AutoAddGPU" "off"

# 位于现有 Device 段中
Identifier "Video Card (xrdpdev)"
Driver "xrdpdev"
Option "DRMDevice" ""
Option "DRI3" "0"
```

以上是需要修改的片段，不能用它们覆盖整份 `xorg.conf`。远程会话使用 xrdpdev，后面为 HDMI 设置的 fbdev 配置不会被远程 Xorg 读取。

### 6.3 服务与连接

将 `xrdp` 用户加入 `ssl-cert` 组，启用并启动 `xrdp` 与 `xrdp-sesman`。现有 UFW 为 inactive，本次没有更改其规则。

```sh
sudo adduser xrdp ssl-cert
sudo systemctl enable --now xrdp xrdp-sesman
sudo systemctl restart xrdp-sesman xrdp
```

Windows 运行 `mstsc`，连接 `192.168.3.181:3389`，在 xrdp 登录窗口选择 **Xorg**，用 kickpi 账户登录。首次可能出现板端自签名证书提示。建议先用 1280×800，确认流畅后再提高分辨率。关闭客户端窗口与在桌面中“注销”不同：前者通常保留远程会话，后者结束会话。

## 7. HDMI 有信号但黑屏：定位到本地 Mali EGL 路径

最初真实 RDP 图形验证通过，本地仅检查了会话进程，未充分验证实际 HDMI 画面。用户随后反馈有信号但全黑，可能看到鼠标。

排查证据：

- HDMI 为 `connected/enabled`，`link-status=Good`，物理输出为 2560×1440@60Hz。
- GNOME Shell 进程存在，但本地截图全黑。
- GNOME Shell 继承了 `COGL_DRIVER=gles2`，加载 `/usr/lib/aarch64-linux-gnu/mali/libEGL.so.1` 和 `libmali.so.1.9.0`。
- 日志出现 `Failed to query buffer age, got error 300d`。
- 独立 RDP 会话已使用 Mesa 软件渲染正常显示。

由此对本地 GNOME Shell 添加 Mesa 覆盖配置：

```text
/home/kickpi/.config/systemd/user/org.gnome.Shell@x11.service.d/50-rk3568-mesa.conf
```

最终板端内容如下，对应 [tools/gnome-shell-rk3568-mesa.conf](tools/gnome-shell-rk3568-mesa.conf)：

```ini
[Service]
UnsetEnvironment=COGL_DRIVER LD_PRELOAD
Environment=LIBGL_ALWAYS_SOFTWARE=1
Environment=GALLIUM_DRIVER=llvmpipe
Environment=__GLX_VENDOR_LIBRARY_NAME=mesa
Environment=__EGL_VENDOR_LIBRARY_FILENAMES=/usr/share/glvnd/egl_vendor.d/50_mesa.json
Environment=LD_LIBRARY_PATH=/usr/lib/aarch64-linux-gnu
Environment=CLUTTER_VBLANK=none
Environment=vblank_mode=0
Environment=LIBGL_DRI3_DISABLE=1
```

最后三项是在后续点击/刷新排障中加入并保留的尝试，不应将它们单独认定为修复原因。该文件及父目录归 kickpi 所有，文件权限为 `0644`。重新载入用户服务定义：

```sh
runuser -u kickpi -- env \
  XDG_RUNTIME_DIR=/run/user/1000 \
  DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus \
  systemctl --user daemon-reload
```

再重新登录本地桌面，使 GNOME Shell 进程使用新环境。检查到进程加载 Mesa EGL/GLX/Gallium 后，截图恢复了顶部栏和 Dock，用户也确认 HDMI 能看到桌面。

但这一步只解决了黑屏，尚未解决下一阶段的交互画面更新异常。此前 [HDMI 恢复截图](rk3568-data/kickpi-hdmi-after.png) 是此中间阶段的 HDMI+DSI 扩展画面，不能作为最终 fbdev 输出布局的证据。

## 8. 鼠标能移动、点击无视觉反应：切换本地 fbdev

用户继续反馈鼠标可以移动，但点击终端或文件夹没有反应。诊断中观察到：

- `xinput` 能收到鼠标 ButtonPress / ButtonRelease，不能仅凭表面现象判断 USB 鼠标损坏。
- GNOME Shell 的 D-Bus Ping 可响应，应用窗口能够被创建，但没有正常合成显示。
- 一度出现 `_NET_ACTIVE_WINDOW=0`，桌面图标进程 DING 窗口只有约 66×32，而不是整个桌面尺寸。
- 板厂 modesetting/glamor 配置使用 `FlipFB=always`，日志有 `crtc-74 flip timeout`。

本轮尝试及结果：

| 尝试 | 实际结果 |
|---|---|
| `PageFlip=false`、`FlipFB=never` | flip timeout 消失，但用户仍反馈点击无视觉反应 |
| modesetting 的 `AccelMethod=none`、`ShadowFB=true` | 本机板厂 Xorg 崩溃，已撤回 |
| 改用 EXA | 本机板厂 Xorg 崩溃，已撤回 |
| 增加 Mesa 的 vblank / DRI3 环境限制 | 在 glamor 路径下仍未恢复交互更新 |
| 本地 Xorg 改用 fbdev `/dev/fb0` | 应用窗口布局恢复，用户确认点击能够打开窗口 |

这些失败尝试不属于推荐配置，也不能推广为所有 RK3568 镜像的共同问题。最终替换的是 `/etc/X11/xorg.conf.d/20-modesetting.conf`；文件名沿用原名，但内容已不再使用 modesetting：

```xorg
# Local framebuffer fallback for GNOME on RK3568.
Section "ServerFlags"
    Option "AutoAddGPU" "false"
EndSection
Section "Device"
    Identifier "Rockchip Graphics"
    Driver "fbdev"
    Option "fbdev" "/dev/fb0"
    Option "ShadowFB" "true"
EndSection
Section "Monitor"
    Identifier "Default Monitor"
EndSection
Section "Screen"
    Identifier "Default Screen"
    Device "Rockchip Graphics"
    Monitor "Default Monitor"
    DefaultDepth 24
EndSection
```

替换前的原文件已备份为 `/root/codex-gnome-rdp-backup/20-modesetting.before-click-fix.conf`。其主要特征是 `Driver=modesetting`、`AccelMethod=glamor`、`DRI=2`、`FlipFB=always`、`NoEDID=true`、`UseGammaLUT=true`。

重启 LightDM 后，fbdev 提供的软件 GLX 路径能够正常更新本地桌面。初始化时曾有 `FBIOPUTCMAP Invalid argument`，`xrandr` 也会报告无法取得 `default` 输出的 gamma 大小；当前这些提示未阻止用户确认的显示与交互，不能仅凭提示推断桌面仍不可用。

## 9. fbdev 尺寸不匹配：800×1280 调整为 2560×1440

切换 fbdev 后点击恢复，但桌面沿用了板载 DSI 屏的 800×1280 尺寸，与 HDMI 显示器不匹配。读取 `/dev/fb0` 的 `FBIOGET_VSCREENINFO`，前八个无符号整数字段为：

```text
调整前：(800, 1280, 2560, 1440, 0, 0, 32, 0)
调整后：(2560, 1440, 2560, 1440, 0, 0, 32, 0)
字段：  xres, yres, xres_virtual, yres_virtual, xoffset, yoffset, bpp, grayscale
```

已分配虚拟 framebuffer 为 2560×1440，足以容纳 HDMI 的目标尺寸。因此本次只修改可见宽高，保留其他参数。实际执行的关键操作如下，供理解和维护；会结束本地桌面，不能在有未保存工作时直接运行：

```sh
sudo systemctl stop lightdm
sudo python3 - <<'PY'
import fcntl
import struct

with open('/dev/fb0', 'r+b', buffering=0) as f:
    info = bytearray(160)
    fcntl.ioctl(f, 0x4600, info)  # FBIOGET_VSCREENINFO
    struct.pack_into('2I', info, 0, 2560, 1440)
    fcntl.ioctl(f, 0x4601, info)  # FBIOPUT_VSCREENINFO
    fcntl.ioctl(f, 0x4600, info)
    print(struct.unpack_from('8I', info))
PY
sudo systemctl start lightdm
```

这里的尺寸与结构处理针对本次 ARM64 Linux framebuffer 实测环境；换屏、换镜像或改变分配尺寸后应重新核查，不能盲目套用。`/sys/class/drm/card0-HDMI-A-1/modes` 首选模式为 2560×1440。

最后读取本地 Xorg：

```sh
sudo env DISPLAY=:0 XAUTHORITY=/var/run/lightdm/root/:0 xrandr --current
```

结果核心内容：

```text
Screen 0: minimum 2560 x 1440, current 2560 x 1440, maximum 2560 x 1440
default connected primary 2560x1440+0+0
   2560x1440      0.00*
```

`0.00` 是 fbdev 虚拟输出报告的模式信息，不能解释为 HDMI 物理链路刷新率为零。fbdev 当前只向 Xorg 提供一个逻辑输出 `default`，不再是最初 HDMI 与 DSI 的独立扩展桌面。

**持久性边界：** Xorg 的 fbdev 配置、GNOME Shell 的 Mesa 覆盖文件已写入磁盘；上述 ioctl 设置的可见尺寸属于运行时状态。本次没有部署 framebuffer 开机设置脚本或 LightDM `ExecStartPre`，也没有整板重启验证。如果启动时内核重新选择 800×1280，桌面尺寸可能再次不匹配。后续如需自动化，应在 Xorg 启动前读取 HDMI 模式、检查虚拟缓冲区容量，再设置可见尺寸，并处理未接 HDMI 的情况。

## 10. 键盘排查与用户最终确认

用户最初反馈尺寸已正常，但终端内无法输入 `abc`。当时终端已有焦点，输入源为 `[('xkb', 'us')]`，Logitech USB Receiver 键盘设备启用并连接到 Xorg 主键盘，设备节点为 `/dev/input/event11`。

一次限时 XInput 采样未记录到按键，但采样窗口可能与用户操作时间错开，不能据此认定键盘、USB 接收器或 IBus 有故障。因此没有基于该结果删除 IBus、改键盘驱动或继续重启桌面。

随后用户更正：**“看错了，可以输入键盘”**。至此用户确认的结果为：

| 项目 | 最终确认 |
|---|---|
| HDMI 桌面显示 | 正常 |
| HDMI 桌面尺寸 | 正常，当前 2560×1440 |
| 鼠标移动和点击 | 可以点击并有反应 |
| 键盘输入 | 用户已确认可以输入 |

这次键盘问题未形成可复现故障，也没有单独的键盘修复变更。

## 11. RDP 验证与最后状态核对

初次部署时进行了真实 RDP 验证，而不只检查服务进程：

1. Windows `192.168.3.34` 对板端 3389 的 `Test-NetConnection` 返回 `TcpTestSucceeded=True`。
2. 板端 FreeRDP 客户端连接 `127.0.0.1:3389`，kickpi 认证成功，创建独立 `:10` Xorg 会话。
3. 远程环境包含 `XDG_CURRENT_DESKTOP=ubuntu:GNOME`、`GNOME_SHELL_SESSION_MODE=ubuntu`、`XDG_SESSION_TYPE=x11`，窗口管理器为 GNOME Shell。
4. 读取远程实际截图，确认顶部栏、Dock、背景及图标。
5. 在远程会话启动 GNOME Terminal，输出验证文字及 `uname -srmo`，测试终端退出码为 0。
6. 测试后结束客户端和测试会话 `c7`，本地会话继续运行。

FreeRDP 测试超时断开日志末尾出现发送错误，对应主动结束测试，不否定此前已成功认证和运行桌面的证据。尚未由用户使用 Windows mstsc 完成人工功能验收，也未验证远程音频、打印和文件重定向。

本次最终只读复核：

| 检查 | 结果 |
|---|---|
| `systemctl is-active lightdm xrdp xrdp-sesman` | 三项均 active |
| TCP 3389 | xrdp 监听 `*:3389` |
| TCP 3350 | sesman 监听回环 `[::1]:3350` |
| `dpkg --audit` | 无输出 |
| `apt-mark showhold` 数量 | 2348 |
| 本地 Xorg | fbdev，当前 2560×1440 |
| framebuffer 前八字段 | `(2560, 1440, 2560, 1440, 0, 0, 32, 0)` |
| 最后一次 HDMI 人工反馈 | 显示、尺寸、点击、键盘均正常 |

真实 RDP 登录测试发生在后续 HDMI fbdev 排障之前；最终重新确认了 RDP 服务和监听状态，没有再重复完整 RDP 图形登录测试。两条 Xorg 配置路径已隔离。

证据和关联文件：

- [初次部署与验证记录](Rk3568-gnome-rdp.md)
- [初次真实 RDP 验证 JSON](rk3568-data/kickpi-gnome-rdp-validation.json)：属于初次验证快照，不包含后续全部 HDMI 变更。
- [真实 RDP 桌面截图](rk3568-data/kickpi-ubuntu-rdp.png)
- [真实 RDP 终端截图](rk3568-data/kickpi-ubuntu-rdp-app.png)
- [HDMI 黑屏截图](rk3568-data/kickpi-hdmi-before.png)
- [Mesa 切换后的中间阶段截图](rk3568-data/kickpi-hdmi-after.png)
- [临时诊断脚本](tools/check_xrdp_gnome.py)：用于技术检查，不是开机服务。

## 12. 维护、限制与恢复

软件渲染会占用 RK3568 的 CPU，高分辨率、多应用和本地/远程同时使用时负担更高，因此关闭了桌面动画。当前方案优先保证基本桌面可用，未验证视频硬件加速、3D 性能、多屏独立布局和显示器热插拔后的自动适配。不要把当前 fbdev 单逻辑输出配置当作完整的 HDMI+DSI 多屏方案。

常用只读检查：

```sh
systemctl status lightdm xrdp xrdp-sesman --no-pager
ss -lntp | grep -E '3389|3350'
loginctl list-sessions
journalctl -b -u lightdm --no-pager -n 80
tail -n 80 /var/log/Xorg.0.log
tail -n 80 /var/log/xrdp.log /var/log/xrdp-sesman.log
# 远程显示号不一定为 10，按实际会话选择日志：
tail -n 80 /home/kickpi/.xorgxrdp.10.log
```

卡住的远程会话可在 `loginctl list-sessions` 中识别后，对指定 ID 使用 `sudo loginctl terminate-session 会话ID`，不要误结束 seat0 或 SSH 会话。重启 LightDM 会退出本地桌面；重启 xrdp/sesman 可能影响远程连接。

如需回退，应区分三个层次，先保存当前文件，再按目标恢复：

1. **恢复板厂本地 Xorg：** 将备份的 `20-modesetting.before-click-fix.conf` 复制回 `/etc/X11/xorg.conf.d/20-modesetting.conf`。这会撤销 fbdev，但在当前 GNOME 下可能重现点击/刷新异常，不应单独当作修复操作。
2. **撤销 GNOME Mesa 覆盖：** 将 `50-rk3568-mesa.conf` 移出对应 `.service.d` 目录，执行 kickpi 用户的 `systemctl --user daemon-reload` 后重新登录。当前 GNOME 可能再次黑屏；XFCE 不使用该 GNOME Shell 服务覆盖。
3. **恢复原 XFCE 会话：** 移出新增的 `90-ubuntu-gnome.conf` 和当前 `.dmrc`，从备份恢复 AccountsService 的 kickpi 文件及 `onboard.desktop`，恢复正确属主，再重新启动 AccountsService 和 LightDM。若目标是恢复板厂显示栈，还需同时处理第 1 项。

本地回退不自动撤销 RDP：`/home/kickpi/startwm.sh` 仍会为 kickpi 启动远程 GNOME；xrdp 原始配置在备份目录 `xrdp/` 中。无需为了切回 XFCE 卸载 GNOME、全量回退依赖或清空系统。

本文按“已安装配置”“诊断中的尝试”“仅运行时生效的设置”和“用户实际确认”分别记录，未将尚未实施的分辨率开机恢复写成已完成操作。

## 13. 2026-11-23：保留 GNOME，将本地 DSI 桌面切换到 XFCE

本次通过 `kickpi@192.168.3.181` 连接。`192.168.3.1` 实际为当时电脑的网关，未开放 SSH。用户确认使用板载 DSI 屏，且触摸可以生效，但响应极慢。

切换前实测：本地 Xorg/GNOME 均为 800×1280、缩放为 1；Goodix 坐标范围为 800×1280，坐标变换与校准矩阵均为单位矩阵。一次采集在 Xorg 记录到 32 次 RawTouchBegin、32 次 RawTouchEnd 和 146 次 RawTouchUpdate，连续滑动的部分事件间隔约 15 毫秒。这证明采样时触摸事件可以到达 Xorg，但未测量应用处理与屏幕呈现的完整延迟。

当时 GNOME 使用 fbdev 和强制 llvmpipe 软件渲染；连续两次一秒采样中 GNOME Shell 占用约 195% 和 188% CPU。可用内存约 2.4 GiB。证据主要指向桌面渲染开销，未将其解释为已经排除所有输入层问题。

用户要求“GNOME 不删除，仅先切换为已有 XFCE”。已执行：

- 在板端 `/root/codex-local-xfce-20261123-111021/` 备份原 `.dmrc`、AccountsService 用户文件，并记录新增覆盖文件此前不存在；对应关系保存在 `manifest.json`。
- 新增 `/etc/lightdm/lightdm.conf.d/99-local-xfce.conf`，将 `user-session` 和 `autologin-session` 设为 `xfce`；原 `90-ubuntu-gnome.conf` 保留。
- 将 `/home/kickpi/.dmrc` 的 Desktop/Session 设为 `xfce`，通过 AccountsService D-Bus 同步 Session 和 XSession。
- 重启 LightDM，结束原本地 GNOME 会话并自动启动 XFCE。未卸载 GNOME，未修改合成器设置、触摸配置或现有 fbdev 配置，未重启整板。

切换后已确认 `xfce4-session`、`xfwm4`、`xfce4-panel`、`xfdesktop` 运行，本地窗口管理器已替换，显示仍为 800×1280。LightDM、xrdp、xrdp-sesman 均 active。RDP 的 `/home/kickpi/startwm.sh` 和本地 `/etc/X11/xorg.conf.d/20-modesetting.conf` 的 SHA-256 与切换前一致；本次没有重复完整 RDP 图形登录验证。

GNOME 可后续切回：撤销新增的 `99-local-xfce.conf`，恢复 `.dmrc` 并将 AccountsService 的 Session/XSession 改回 `ubuntu-xorg`，再重启本地显示管理器。该操作会关闭当前本地窗口，应在用户要求切回时执行。

本次使用的维护脚本为 `tools/switch_local_xfce.py`；SSH 诊断工具为 `tools/diagnose_touchscreen.py`，按此前核对的开发板主机公钥验证身份，密码通过运行环境传入，不保存在脚本中。切换已由进程、会话和显示配置核对。用户随后确认触摸流畅，但反馈终端打不开，处理见下一节。

## 14. XFCE 默认终端修复

切换后，系统的 `x-terminal-emulator` 自动选择了 `/usr/bin/zutty`，实测启动报 `eglInitialize() failed`，退出码为 255；已有 `xfce4-terminal` 能正常启动。用户级 `~/.config/xfce4/helpers.rc` 此前只有 `TerminalEmulatorDismissed=true`，没有明确选定终端；Ctrl+Alt+T 和 Super+T 均调用 `exo-open --launch TerminalEmulator`。

用户授权自动修改后，先备份到板端 `/root/codex-terminal-20261123-111919/`，再将用户级首选项设为 `TerminalEmulator=xfce4-terminal`，同时执行 `update-alternatives --set x-terminal-emulator /usr/bin/xfce4-terminal.wrapper`。没有卸载 Zutty 或其他终端。维护脚本为 `tools/configure_xfce_terminal.py`。

验证时，系统默认终端和 XFCE helper 的测试命令均返回 0；随后通过 `exo-open --launch TerminalEmulator` 打开交互终端，Xorg 窗口树确认存在 `Terminal - kickpi@kickpi: ~` 窗口。无需重启桌面即可生效。SSH 启动测试缺少 SESSION_MANAGER 会产生会话管理警告，未阻止终端打开；该测试不等同于已经人工验证键盘输入。

XFCE 设置管理器可通过 Alt+F2 输入 `xfce4-settings-manager` 打开，无需桌面上存在 Settings 快捷方式。
