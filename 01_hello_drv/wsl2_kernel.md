# WSL2 中编译并运行 Linux 驱动（hello_drv）完整过程

本文记录在 WSL2 中搭建 Linux 内核模块编译环境、自编译内核、编译并加载 `hello_drv` 字符设备驱动的完整过程。

## 0. 目标

- 环境：Windows 11 + WSL2（Ubuntu 22.04）
- 目标：把针对 ARM 板子（RK3399 / linux-4.4）的 `hello_drv` 驱动，在 WSL2 本机编译并 `insmod` 运行。

## 1. 环境检查

```bash
wsl -l -v                 # 查看发行版
wsl uname -r              # 6.6.87.2-microsoft-standard-WSL2
wsl ls /lib/modules       # 查看是否有内核构建树
```

关键结论：

- WSL2 内核版本 `6.6.87.2-microsoft-standard-WSL2`
- 有 `gcc`、`make`，但**缺少内核构建树** `/lib/modules/.../build`
- WSL 用微软自家内核，apt 里的 `linux-headers-generic`（5.15）版本对不上，必须从微软 `WSL2-Linux-Kernel` 源码生成构建树。

确认内核支持加载模块：

```bash
cat /proc/sys/kernel/modules_disabled   # 0，可加载模块
cat /proc/modules                       # 有已加载模块
zcat /proc/config.gz | grep -E 'CONFIG_MODULES|CONFIG_MODVERSIONS|CONFIG_MODULE_SIG'
# CONFIG_MODULES=y
# CONFIG_MODVERSIONS=y        <- 关键：需要 Module.symvers 匹配符号 CRC
# # CONFIG_MODULE_SIG is not set   <- 无需签名
```

## 2. 安装编译依赖

用 root（`wsl -u root` 免密）：

```bash
wsl -u root bash -c "apt-get update -qq && \
  DEBIAN_FRONTEND=noninteractive apt-get install -y -qq \
  build-essential libncurses-dev bison flex libssl-dev libelf-dev bc dwarves"
```

> 说明：`dwarves`（提供 `pahole`）用于生成 BTF，若不做完整 `vmlinux` 链接可后装；此处一并装上。

## 3. 下载内核源码

找到与运行内核完全匹配的 tag `linux-msft-wsl-6.6.87.2`（对应 `6.6.87.2-microsoft-standard-WSL2`）。

git clone 因 HTTP2 网络问题失败，改用 tarball 下载：

```bash
cd /home/jzx
curl -L -o wsl-kernel.tar.gz \
  https://github.com/microsoft/WSL2-Linux-Kernel/archive/refs/tags/linux-msft-wsl-6.6.87.2.tar.gz
tar xzf wsl-kernel.tar.gz
mv WSL2-Linux-Kernel-linux-msft-wsl-6.6.87.2 WSL2-Linux-Kernel
```

## 4. 生成内核构建树

```bash
cd /home/jzx/WSL2-Linux-Kernel

# 用微软的 config 生成 .config
cp Microsoft/config-wsl .config
make olddefconfig

# 生成模块编译所需的头文件、scripts、边界头等
make -j16 modules_prepare
```

此时会生成 `include/generated/autoconf.h`、`include/config/kernel.release` 等，但**不会生成 `Module.symvers`**。

## 5. 编译 vmlinux 生成符号表

由于 `CONFIG_MODVERSIONS=y`，编译外部模块需要内核导出符号的 CRC（`Module.symvers`）：

```bash
make -j16 vmlinux
```

> 中途会因缺 `pahole` 在 BTF 生成步骤失败（`Failed to generate BTF for vmlinux`），
> 但 `MODPOST vmlinux.symvers` 已先行完成。安装 `dwarves` 后重跑即可继续。

生成 `vmlinux.symvers` 后，复制为 `Module.symvers`（外部模块编译读取的是它）：

```bash
cp vmlinux.symvers Module.symvers
```

验证驱动用到的符号都在：

```bash
grep -E '(printk|copy_to_user|copy_from_user|register_chrdev|class_create)' Module.symvers
```

## 6. 编译 bzImage（完整内核镜像）

```bash
make -j16 bzImage
# 产物：arch/x86/boot/bzImage
```

## 7. 代码适配（新旧内核 API 差异）

`hello_drv.c` 是为 linux-4.4 写的，内核 6.4+ 移除了 `class_create` 的 owner 参数。
用条件编译兼容新旧内核：

```c
#include <linux/version.h>   // 新增

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6, 4, 0)
	hello_class = class_create("hello_class");
#else
	hello_class = class_create(THIS_MODULE, "hello_class");
#endif
```

## 8. 编译驱动

在工程目录（drvfs 上可直接编译）用命令行覆盖 `KERN_DIR`（不改动原 Makefile）：

```bash
cd '/mnt/e/vscode_code/cpp_code/doc_and_source_for_livestream/.../01_hello_drv'
make KERN_DIR=/home/jzx/WSL2-Linux-Kernel
```

产物：`hello_drv.ko`、`hello_drv_test`。

## 9. 遇到的问题：module_layout CRC 不匹配

直接 `insmod` 报 `Invalid module format`，dmesg 显示：

```
hello_drv: disagrees about version of symbol module_layout
```

`insmod -f` 强制加载也失败：

```
module: x86/modules: Invalid relocation target, existing value is nonzero ...
```

**根因**：微软官方内核用 Azure Linux 工具链（gcc 12/13）编译，本地用 gcc 11，
导致 `module_layout` 符号的 MODVERSIONS CRC 不一致（config 实质一致，`CONFIG_RANDSTRUCT_NONE=y`）。

**解决**：自编译一个与驱动同工具链（gcc 11）的内核，替换 WSL 内核，使 `module_layout` CRC 完全匹配。

验证 CRC 一致：

```bash
grep module_layout /home/jzx/WSL2-Linux-Kernel/Module.symvers
modprobe --dump-modversions hello_drv.ko | grep module_layout
# 两者均为 0x371d14fe
```

## 10. 替换 WSL2 内核

1. 复制 `bzImage` 到 Windows 侧：

```bash
mkdir -p '/mnt/c/Users/Jiang ZiXian/wsl-kernel'
cp /home/jzx/WSL2-Linux-Kernel/arch/x86/boot/bzImage \
   '/mnt/c/Users/Jiang ZiXian/wsl-kernel/bzImage'
```

2. 创建/修改 `C:\Users\Jiang ZiXian\.wslconfig`：

```ini
[wsl2]
kernel=C:\\Users\\Jiang ZiXian\\wsl-kernel\\bzImage
```

3. 重启 WSL：

```powershell
wsl --shutdown
wsl cat /proc/version   # 应显示 (jzx@...) 和 gcc 11.4.0，编译日期为当天
```

## 11. 加载并测试驱动

```bash
cd '/mnt/e/.../01_hello_drv'
make KERN_DIR=/home/jzx/WSL2-Linux-Kernel

sudo insmod hello_drv.ko            # 成功，/dev/hello 创建
sudo ./hello_drv_test -w abc
sudo ./hello_drv_test -r            # 输出：APP read : abc
sudo rmmod hello_drv
```

dmesg 会看到 `hello_init`/`hello_drv_open`/`hello_drv_write`/`hello_drv_read`/`hello_exit` 各函数的 `printk` 输出。

## 12. 注意事项

- **恢复官方内核**：删除 `C:\Users\Jiang ZiXian\.wslconfig` 后 `wsl --shutdown` 即可。
- **副作用**：替换内核后，微软预编译的模块（`bridge`、`kvm_intel`、`tun` 等，Docker/VPN 用）会因 CRC 不匹配无法加载。若需要 Docker，请恢复官方内核（但那样又无法 insmod 自编驱动）。
- **后续编译**：每次编译驱动都用 `make KERN_DIR=/home/jzx/WSL2-Linux-Kernel`，原 Makefile 中 `KERN_DIR` 指向 RK3399 的 4.4 内核，保持不变。
- **Clock skew 警告**：在 `/mnt/e`（drvfs）上编译会出现文件时间戳在未来 1~2 秒的 `Clock skew detected` 警告，属 drvfs 时间戳精度问题，不影响产物。
