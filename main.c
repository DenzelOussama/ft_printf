#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include "ft_printf.h"

extern ssize_t __real_write(int fd, const void *buf, size_t count);

ssize_t __wrap_write(int fd, const void *buf, size_t count) {
    static size_t n = 0;
    if (++n > 9) {
        errno = EIO;
        return -1;
    }
    return __real_write(fd, buf, count);
}

int main()
{
    char *i = "strs";
    int b = ft_printf("read: %p",i);
    dprintf(2,"\n%i --- %p",b,i);
}