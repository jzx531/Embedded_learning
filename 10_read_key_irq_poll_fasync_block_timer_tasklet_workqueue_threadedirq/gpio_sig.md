# GPIO 按键驱动异步信号通知机制解析

> 对应源码：`gpio_key_drv.c`
> 本文解析驱动里的 fasync/SIGIO 异步通知机制，并深入 Linux 内核信号处理的内部实现。

---

## 一、整体流程图

```text
应用层                                    内核                                 驱动
------                                    ----                                 ----
signal(SIGIO, handler)                                                          |
fcntl(fd, F_SETOWN, getpid())  ---> 设置 file->f_owner(pid)                    |
fcntl(fd, F_SETFL, O_ASYNC)     ---> 调用 f_op->fasync(fd, file, 1) ---> fasync_helper 登记
                                          |                                     |
                                          |   (驱动把 struct fasync_struct      |
                                          |    节点插入 button_fasync 链表)      |
                                          |                                     |
                                          |                    按键触发定时器回调 |
                                          |                          key_timer_expire
                                          |                                |
                                          |<------ kill_fasync(..., SIGIO, POLL_IN)
                                          |                                |
                                      send_sigio                           |
                                          |                                |
                                      send_signal (加入 pending 队列)        |
                                          |                                |
                                   signal_wake_up (唤醒进程)                 |
                                          |                                |
[进程返回用户态前检查 pending 信号]           |                                |
   do_signal -> handle_signal               |                                |
[跳转到用户态 handler 执行] ----------------------------------------------------|
```

---

## 二、应用层如何启用异步通知

要使用异步通知，应用层需要做三件事：

```c
#include <signal.h>
#include <fcntl.h>

void sig_handler(int signum)
{
    // 收到 SIGIO 后读按键值
    read(fd, &key, 4);
}

int main(void)
{
    // 1. 注册信号处理函数
    signal(SIGIO, sig_handler);

    // 2. 设置本进程为文件属主（内核据此知道把信号发给谁）
    fcntl(fd, F_SETOWN, getpid());

    // 3. 打开异步通知标志（触发驱动 fasync() 回调）
    int flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_ASYNC);

    while (1) sleep(1);   // 主循环休眠，等待信号
}
```

---

## 三、驱动层如何实现

### 3.1 登记：fasync 回调

```c
static int gpio_key_drv_fasync(int fd, struct file *file, int on)
{
    if (fasync_helper(fd, file, on, &button_fasync) >= 0)
        return 0;
    else
        return -EIO;
}

static struct file_operations gpio_key_drv = {
    ...
    .fasync  = gpio_key_drv_fasync,
};
```

`fasync_helper()`（内核 `fs/fcntl.c`）：

```c
int fasync_helper(int fd, struct file *filp, int on, struct fasync_struct **fapp)
{
    if (!on)
        return fasync_remove_entry(filp, fapp);   // 关闭异步通知：从链表移除
    return fasync_add_entry(fd, filp, fapp);      // 打开异步通知：加入链表
}
```

`fasync_add_entry()` 分配一个 `struct fasync_struct`，记录 `fa_file`（文件）和 `fa_fd`（fd），然后**头插法**插入 `button_fasync` 链表：

```c
struct fasync_struct *new;
new->fa_file = filp;
new->fa_fd   = fd;
new->fa_next = *fapp;   // 新节点指向原表头
*fapp        = new;     // 表头更新为新节点
```

### 3.2 触发：kill_fasync

按键稳定后，在定时器回调里向所有登记的进程发信号：

```c
static void key_timer_expire(unsigned long data)
{
    ...
    put_key(key);
    wake_up_interruptible(&gpio_key_wait);        // 唤醒阻塞读
    kill_fasync(&button_fasync, SIGIO, POLL_IN);  // 发异步信号
}
```

`kill_fasync()`（内核 `fs/fcntl.c`）：

```c
void kill_fasync(struct fasync_struct **fp, int sig, int band)
{
    while (*fp) {
        struct fasync_struct *fa = *fp;
        *fp = fa->fa_next;                       // 遍历链表
        ...
        send_sigio(&fa->fa_file->f_owner, fa->fa_fd, band);  // 逐个发送
        ...
    }
}
```

---

## 四、内核信号处理内部机制

### 4.1 F_SETOWN 设置文件属主

`fcntl(fd, F_SETOWN, getpid())` 最终设置 `struct file->f_owner`（`struct fown_struct`），内核据此确定信号接收者：

```c
struct fown_struct {
    rwlock_t lock;
    struct pid *pid;          // 属主进程的 pid
    enum pid_type pid_type;   // PID / PGID / TGID 等
    kuid_t euid, uid;
    int signum;               // 要发送的信号，默认 SIGIO
};
```

> `F_SETOWN` 默认 `pid_type = PIDTYPE_TGID`，即信号发给整个**线程组**；用 `F_SETOWN_EX` 可以更精细地指定。

### 4.2 O_ASYNC 标志与 fasync 回调的触发

`fcntl(fd, F_SETFL, flags | O_ASYNC)` 在内核 `setfl()` 中：

```c
if ((arg ^ filp->f_flags) & FASYNC) {   // O_ASYNC 对应 FASYNC 位发生变化
    if (filp->f_op->fasync)
        filp->f_op->fasync(fd, filp, (arg & FASYNC) ? 1 : 0);
}
```

即：设置/清除 `O_ASYNC` 都会回调驱动的 `.fasync`，从而完成登记/注销。

### 4.3 kill_fasync → send_sigio → send_signal

**第 1 步：`send_sigio()`**（`fs/fcntl.c`）根据 `f_owner` 找到目标进程：

```c
void send_sigio(struct fown_struct *fown, int fd, int band)
{
    ...
    type = fown->pid_type;
    pid  = fown->pid;
    ...
    // 根据 pid_type(PID/PGID/TGID) 遍历找到目标 task_struct
    send_sigio_to_task(p, ..., fd, band, type);
}
```

**第 2 步：`send_sigio_to_task()`** 构造 `siginfo` 并发送：

```c
static void send_sigio_to_task(struct task_struct *p, ...)
{
    struct kernel_siginfo si;
    clear_siginfo(&si);
    si.si_signo = sig;      // SIGIO
    si.si_errno = 0;
    si.si_code  = SI_SIGIO; // 或根据 band 映射为 SI_KERNEL 等
    si.si_fd    = fd;
    si.si_band  = band;     // POLL_IN
    ...
    send_sig_info(sig, &si, p);
}
```

**第 3 步：`send_sig_info()` → `do_send_sig_info()` → `send_signal()`**（`kernel/signal.c`）真正把信号投递到进程。

### 4.4 信号投递：send_signal / __send_signal

```c
static int send_signal(int sig, struct kernel_siginfo *info,
                       struct task_struct *t, enum pid_type type)
{
    ...
    return __send_signal(sig, info, t, type, force);
}
```

`__send_signal()` 核心动作：

1. 检查目标进程是否已忽略/阻塞该信号，若已忽略则直接返回。
2. 分配一个 `struct sigqueue`（`__sigqueue_alloc`），保存 siginfo。
3. 把该 sigqueue 挂入目标进程的**信号挂起队列**（`task->pending` 或线程组共享的 `signal->shared_pending`）。
4. 调用 `complete_signal()` 唤醒目标进程。

```text
struct task_struct
   |
   +-- struct signal_struct *signal
   |      +-- shared_pending   (线程组共享挂起信号队列)
   |
   +-- struct sigpending pending   (本线程私有挂起信号队列)
```

### 4.5 唤醒进程：complete_signal → signal_wake_up

```c
static void complete_signal(int sig, struct task_struct *p, enum pid_type type)
{
    ...
    signal_wake_up(t, sig == SIGKILL);
}

void signal_wake_up_state(struct task_struct *t, unsigned int state)
{
    set_tsk_thread_flag(t, TIF_SIGPENDING);   // 标记"有信号待处理"
    ...
    wake_up_state(t, state);                  // 唤醒休眠中的进程
}
```

关键：设置 `TIF_SIGPENDING` 标志，并把进程状态置为 `TASK_RUNNING` 唤醒它。之后内核在**返回用户空间**时检查这个标志。

### 4.6 信号处理：do_signal → handle_signal

进程被唤醒、重新被调度运行后，在内核即将**返回到用户态**的路径上（`entry.S` 的 `ret_to_user` / `do_work_pending`）检查 `TIF_SIGPENDING`，若有则调用 `do_signal()`：

```text
返回到用户态
   |
   v
检查 TIF_SIGPENDING 标志
   |
   |-- 有信号待处理 --> do_signal()
   |        |
   |        |-- 忽略/默认动作(如终止进程)
   |        |
   |        |-- 用户态 handler --> handle_signal()
   |                 |
   |                 |-- 构造用户态栈帧(保存被中断现场)
   |                 |-- setup_rt_frame / setup_frame
   |                 v
   |           修改返回地址指向用户态 handler
   v
返回用户态，执行 handler
```

`handle_signal()` 会在用户栈上建立一个信号帧（保存 `PC`、寄存器等现场），并把返回到用户态后的**下一条指令地址**改为信号处理函数入口。这样进程回到用户态后，第一件事就是执行用户的 `sig_handler`。

处理完信号后，通过 `sigreturn`/`rt_sigreturn` 恢复现场，继续执行主流程。

---

## 五、完整调用链总结

```text
【登记阶段】
fcntl(fd, F_SETOWN, getpid())
   └── 设置 file->f_owner.pid / pid_type

fcntl(fd, F_SETFL, flags | O_ASYNC)
   └── setfl() 检测 FASYNC 位变化
        └── file->f_op->fasync(fd, file, 1)
             └── gpio_key_drv_fasync
                  └── fasync_helper -> fasync_add_entry
                       └── 节点头插到 button_fasync 链表

【触发阶段】
按键中断 -> 定时器去抖 -> key_timer_expire
   └── kill_fasync(&button_fasync, SIGIO, POLL_IN)
        └── 遍历链表 send_sigio(f_owner, fd, POLL_IN)
             └── send_sigio_to_task: 构造 siginfo{signo=SIGIO, si_band=POLL_IN}
                  └── send_sig_info -> do_send_sig_info -> send_signal
                       └── __send_signal: 分配 sigqueue 挂入 pending 队列
                            └── complete_signal -> signal_wake_up
                                 └── 置 TIF_SIGPENDING + 唤醒进程

【处理阶段】
进程被唤醒 -> 返回用户态前检测 TIF_SIGPENDING
   └── do_signal -> handle_signal -> 设置用户栈帧
        └── 返回用户态执行 sig_handler
```

---

## 六、与阻塞读 / poll 的对比

| 方式 | 机制 | 应用层动作 | 特点 |
|------|------|-----------|------|
| 阻塞读 read | `wait_event_interruptible` + `wake_up_interruptible` | 一直 `read`，无数据则睡眠 | 最简单，但占用一个线程 |
| poll | `poll_wait` 挂等待队列 | `select/poll` | 可同时监听多个 fd |
| 异步通知 | `fasync_helper` + `kill_fasync` | `signal` + `F_SETOWN` + `O_ASYNC` | 进程可做别的，有数据时被信号打断，效率最高 |

---

## 七、关键内核源码位置

| 功能 | 源码位置 |
|------|---------|
| `fasync_helper` / `fasync_add_entry` / `fasync_remove_entry` | `fs/fcntl.c` |
| `kill_fasync` | `fs/fcntl.c` |
| `send_sigio` / `send_sigio_to_task` | `fs/fcntl.c` |
| `setfl`（O_ASYNC/FASYNC 处理） | `fs/fcntl.c` |
| `send_sig_info` / `do_send_sig_info` | `kernel/signal.c` |
| `send_signal` / `__send_signal` / `complete_signal` | `kernel/signal.c` |
| `signal_wake_up` | `kernel/signal.c` |
| `do_signal` / `handle_signal` / `setup_rt_frame` | `arch/<arch>/kernel/signal.c` |
