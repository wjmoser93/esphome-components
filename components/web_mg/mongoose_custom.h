#pragma once
#include "esphome/core/defines.h"
#include "esphome/components/socket/headers.h"

//#define MG_ENABLE_CUSTOM_MILLIS 1
// Helper file to include all socket-related system headers (or use our own
// definitions where system ones don't exist)
//#if defined(USE_ESP8266)
#define MG_ENABLE_TCP 0
#define MG_ENABLE_SOCKET 1
#define MG_ENABLE_LWIP 0
#include <sys/types.h>
#include <ctype.h>
//#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
//#include <netdb.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
/*
extern int accept(int s,struct sockaddr *addr, socklen_t *addrlen);
extern int bind(int s, const struct sockaddr *name, socklen_t namelen) ;
extern int shutdown(int s, int how);
int getpeername (int s, struct sockaddr *name, socklen_t *namelen) ;
//extern int getsockname (int s, struct sockaddr *name, socklen_t *namelen) ;
int getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen) ;
int setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen) ;;
 int close(int s) ;
int connect(int s, const struct sockaddr *name, socklen_t namelen) ;
int listen(int s, int backlog) ;
ssize_t recv(int s, void *mem, size_t len, int flags) ;
ssize_t read(int s, void *mem, size_t len) ;
ssize_t readv(int s, const struct iovec *iov, int iovcnt) ;
ssize_t recvfrom(int s, void *mem, size_t len, int flags,
      struct sockaddr *from, socklen_t *fromlen) ;
ssize_t send(int s, const void *dataptr, size_t size, int flags);
ssize_t sendto(int s, const void *dataptr, size_t size, int flags,
const struct sockaddr *to, socklen_t tolen);
int socket(int domain, int type, int protocol);
*/

//#endif //use esp8266


