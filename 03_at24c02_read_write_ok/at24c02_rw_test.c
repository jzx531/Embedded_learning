/*
 * 用户态读写示例，与内核驱动分开编译。
 * 编译：gcc -std=gnu11 -Wall -Wextra at24c02_rw_test.c -o at24c02_rw_test
 * 运行：./at24c02_rw_test /dev/myat24c02
 *
 * 程序会将 EEPROM 的 0x10～0x13 改写为 11 22 33 44，再读回验证。
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    unsigned char tx[] = { 0x11, 0x22, 0x33, 0x44 };
    unsigned char rx[sizeof(tx)];
    ssize_t n;
    int fd;
    int status = 1;

    if (argc != 2) {
        fprintf(stderr, "usage: %s /dev/myat24c02\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDWR | O_CLOEXEC);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    if (lseek(fd, 0x10, SEEK_SET) == -1) {
        perror("lseek before write");
        goto out;
    }

    do {
        n = write(fd, tx, sizeof(tx));
    } while (n < 0 && errno == EINTR);

    if (n < 0) {
        perror("write");
        goto out;
    }
    if ((size_t)n != sizeof(tx)) {
        fprintf(stderr, "short write: %zd/%zu bytes\n", n, sizeof(tx));
        goto out;
    }

    /* write 会推进文件偏移，必须重新定位才能读回相同位置。 */
    if (lseek(fd, 0x10, SEEK_SET) == -1) {
        perror("lseek before read");
        goto out;
    }

    do {
        n = read(fd, rx, sizeof(rx));
    } while (n < 0 && errno == EINTR);

    if (n < 0) {
        perror("read");
        goto out;
    }
    if ((size_t)n != sizeof(rx)) {
        fprintf(stderr, "short read: %zd/%zu bytes\n", n, sizeof(rx));
        goto out;
    }

    for (size_t i = 0; i < sizeof(rx); ++i)
        printf("addr=0x%02x data=0x%02x\n",
               (unsigned int)(0x10 + i), (unsigned int)rx[i]);

    if (memcmp(tx, rx, sizeof(tx)) != 0) {
        fprintf(stderr, "read-back verification failed\n");
        goto out;
    }

    puts("read-back verification passed");
    status = 0;

out:
    close(fd);
    return status;
}
