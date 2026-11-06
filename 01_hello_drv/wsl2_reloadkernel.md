# 恢复 WSL2 官方内核

本文记录如何把 WSL2 从「自编译内核」恢复回微软官方内核。

## 背景

之前为了让 `hello_drv.ko` 能在本机加载，做了两件事：

1. 在 Windows 侧生成了自编译内核镜像：`C:\Users\Jiang ZiXian\wsl-kernel\bzImage`
2. 创建了配置文件 `C:\Users\Jiang ZiXian\.wslconfig`，内容为：

```ini
[wsl2]
kernel=C:\\Users\\Jiang ZiXian\\wsl-kernel\\bzImage
```

WSL2 启动时会读取 `.wslconfig`，一旦 `kernel=` 指向了自定义镜像，就不会再用微软自带的内核。

所以恢复 = **让 `.wslconfig` 不再指向自编译内核**，然后重启 WSL。

## 恢复方法（任选其一）

### 方法 A：直接删除 .wslconfig（最简单，彻底恢复默认）

```powershell
Remove-Item -LiteralPath "$env:USERPROFILE\.wslconfig"
```

### 方法 B：只注释掉 kernel 行（保留文件，方便以后切换）

把 `C:\Users\Jiang ZiXian\.wslconfig` 里的 `kernel=` 那行前面加 `#` 注释掉：

```ini
[wsl2]
# kernel=C:\\Users\\Jiang ZiXian\\wsl-kernel\\bzImage
```

> `.wslconfig` 是 INI 格式，用 `#` 或 `;` 开头即为注释。
> 以后想再切回自编译内核，把 `#` 去掉即可。

## 重启 WSL 使配置生效

```powershell
wsl --shutdown
```

然后重新打开 WSL（`wsl` 或直接打开 Ubuntu 终端）。

## 验证是否恢复成功

```bash
wsl cat /proc/version
```

- **恢复成功**：显示类似

  ```
  Linux version 6.6.87.2-microsoft-standard-WSL2 (microsoft@...) (gcc (GCC) 12.x.x, ...) ...
  ```

  特征：`(microsoft@...)`、gcc 版本是 12.x/13.x（微软 Azure Linux 工具链）。

- **仍是自编译内核**（未生效）：显示

  ```
  Linux version 6.6.87.2-microsoft-standard-WSL2 (jzx@DESKTOP-JRQOEDE) (gcc (Ubuntu 11.4.0-...) 11.4.0, ...) #2 SMP PREEMPT_DYNAMIC Thu Nov  5 16:45:09 CST 2026
  ```

  特征：`(jzx@...)`、gcc 11.4.0、编译日期是当天。

## 补充说明

1. **恢复后自编驱动就无法 insmod 了**：微软官方内核用不同工具链，`hello_drv.ko` 的 `module_layout` CRC 对不上，会报 `Invalid module format`。这是正常现象。
2. **内核源码/构建树不受影响**：`/home/jzx/WSL2-Linux-Kernel` 和 `C:\Users\Jiang ZiXian\wsl-kernel\bzImage` 都还在，可以留着；`bzImage` 以后切回自编译内核时还用得上。
3. **可随时切换**：删除 `.wslconfig` 用官方内核；恢复 `.wslconfig` 的 `kernel=` 行则用自编译内核，每次切换后都要 `wsl --shutdown` 才能生效。
