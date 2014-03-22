#include "klee/Config/Version.h"
#define _LARGEFILE64_SOURCE
#include "../POSIX/fd.h"
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <klee/klee.h>
#include <string.h>

int socket(int domain, int type, int protocol) {
  mode_t mode = 0;
  int flags = eSocket;
  int a = __fd_open("pathname", flags, mode);
  printf ("\n\nit's me!!!   %d\n\n",a);
  return a;
}

int socketpair (int domain, int type, int protocol, int fds[2]) {
  fds[0] = socket(domain, type, protocol);
  fds[1] = socket(domain, type, protocol);
  if ((fds[0] < 0) || (fds[1] < 0))
     return -1;
  return 0;
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len) {
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
    return 0;
}
int listen(int socket, int backlog) {
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
    return 0;
}

ssize_t send(int socket, const void *buffer, size_t length, int flags) {
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
    return 0;
}

ssize_t recv(int socket, void *buffer, size_t length, int flags) {
    size_t len;
//    int bad_conn;
    char data[4096];
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
//    klee_make_symbolic(&len, sizeof(int), "len");
//    klee_make_symbolic(&bad_conn, sizeof(int), "bad_conn");
    
    if (klee_range(0, 2, "bad_conn") != 0) { 
      errno = ECONNABORTED;
      return -1;
    }
    len = klee_range(0, (length + 1), "recv_len");
    if (len > sizeof(data)) {
       errno = ENOMEM;
       return -1;
    }
    klee_make_symbolic(data, sizeof(data), "data");
    memcpy(buffer, data, len);
    return len;
}

ssize_t sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
    return 0;
}

/*ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len) {
    if (!__fd_is_socket(socket)) {
      errno = EBADF;
      return -1;
    }
    int len;
    klee_make_symbolic(&len, sizeof(int), "len");
    int bad_conn;
    klee_make_symbolic(&bad_conn, sizeof(int), "bad_conn");
    if(bad_conn % 2 != 0) {
      errno = ECONNABORTED;
      return -1;
    }
    len %= length;
    char data[len];
    klee_make_symbolic(data, sizeof(data), "data");
    memcpy(buffer,data,len);
    return len;
}
*/
//int accept (int socket, struct sockaddr *address, socklen_t *address_len) {
//}
