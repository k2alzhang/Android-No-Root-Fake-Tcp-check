#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static int is_proc_net_tcp(const char *path) {
    if (!path) return 0;
    return (strcmp(path, "/proc/net/tcp") == 0 ||
            strcmp(path, "/proc/net/tcp6") == 0);
}

int open(const char *pathname, int flags, ...) {
    static int (*real_open)(const char *, int, ...) = NULL;
    if (!real_open) real_open = dlsym(RTLD_NEXT, "open");
    if (is_proc_net_tcp(pathname)) {
        char template[] = "/tmp/fake_tcp_XXXXXX";
        int fd = mkstemp(template);
        if (fd < 0) return -1;
        ftruncate(fd, 0);
        return fd;
    }
    return real_open(pathname, flags);
}

int openat(int dirfd, const char *pathname, int flags, ...) {
    static int (*real_openat)(int, const char *, int, ...) = NULL;
    if (!real_openat) real_openat = dlsym(RTLD_NEXT, "openat");
    if (is_proc_net_tcp(pathname)) {
        char template[] = "/tmp/fake_tcp_XXXXXX";
        int fd = mkstemp(template);
        if (fd < 0) return -1;
        ftruncate(fd, 0);
        return fd;
    }
    return real_openat(dirfd, pathname, flags);
}

int open64(const char *pathname, int flags, ...) {
    static int (*real_open64)(const char *, int, ...) = NULL;
    if (!real_open64) real_open64 = dlsym(RTLD_NEXT, "open64");
    if (is_proc_net_tcp(pathname)) {
        char template[] = "/tmp/fake_tcp_XXXXXX";
        int fd = mkstemp(template);
        if (fd < 0) return -1;
        ftruncate(fd, 0);
        return fd;
    }
    return real_open64(pathname, flags);
}

int stat(const char *pathname, struct stat *statbuf) {
    static int (*real_stat)(const char *, struct stat *) = NULL;
    if (!real_stat) real_stat = dlsym(RTLD_NEXT, "stat");
    if (is_proc_net_tcp(pathname)) {
        memset(statbuf, 0, sizeof(struct stat));
        statbuf->st_mode = S_IFREG | 0644;
        statbuf->st_nlink = 1;
        statbuf->st_size = 0;
        return 0;
    }
    return real_stat(pathname, statbuf);
}

int lstat(const char *pathname, struct stat *statbuf) {
    static int (*real_lstat)(const char *, struct stat *) = NULL;
    if (!real_lstat) real_lstat = dlsym(RTLD_NEXT, "lstat");
    if (is_proc_net_tcp(pathname)) {
        memset(statbuf, 0, sizeof(struct stat));
        statbuf->st_mode = S_IFREG | 0644;
        statbuf->st_nlink = 1;
        statbuf->st_size = 0;
        return 0;
    }
    return real_lstat(pathname, statbuf);
}

int access(const char *pathname, int mode) {
    static int (*real_access)(const char *, int) = NULL;
    if (!real_access) real_access = dlsym(RTLD_NEXT, "access");
    if (is_proc_net_tcp(pathname)) {
        return 0;  // 返回0表示可访问
    }
    return real_access(pathname, mode);
}
