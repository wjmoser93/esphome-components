#include "esphome/core/defines.h"
#include "esphome/components/socket/socket.h"
 #include <stdint.h>
#include <sys/types.h>

/*
extern "C" uint64_t mg_millis(void) {
    return millis();
}
*/

/*
  int accept(struct sockaddr *addr, socklen_t *addrlen) { return 0;}
  int bind(int s,const struct sockaddr *addr, socklen_t addrlen) { return 0; };
  int close(int s) { return 0; };
  int shutdown(int s,int how) { return 0; };
  int getpeername(int s,struct sockaddr *addr, socklen_t *addrlen) { return 0; };
  int getsockname(int s,struct sockaddr *addr, socklen_t *addrlen) { return 0; };
  int getsockopt(int s,int level, int optname, void *optval, socklen_t *optlen) { return 0; };
  int setsockopt(int s,int level, int optname, const void *optval, socklen_t optlen) { return 0; };
  int listen(int s,int backlog) { return 0; };
  int sendto(int s,const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen) { return 0; };
  int send(int s,const void *buf,size_t len, int flags) { return 0;};
  int recv(int s, void *buf,size_t len, int flags) { return 0;} 
  int recvfrom(int s, void *buf,size_t len, int flags, struct sockaddr *from, socklen_t *fromlen) { return 0;}   
  int select (int s, fd_set * rset, fd_set *wset, fd_set *errofds, struct timeval *timeout) { return 0;}
 int socket(int domain, int type, int protocol) {  return 0;};  
*/
  
extern "C" int accept(int s, struct sockaddr *addr, socklen_t *addrlen) { 

auto sock=static_cast<esphome::socket::Socket*>((void *)s)->accept(addr,addrlen);
return (int) sock.get();
}
extern "C" int bind(int s, const struct sockaddr *name, socklen_t namelen) {  return 0;}; 
extern "C" int shutdown(int s, int how);
extern "C" int getpeername (int s, struct sockaddr *name, socklen_t *namelen) {  return 0;}; 
extern "C" int getsockname (int s, struct sockaddr *name, socklen_t *namelen) {  return 0;}; 
extern "C" int getsockopt (int s, int level, int optname, void *optval, socklen_t *optlen) {  return 0;}; 
extern "C" int setsockopt (int s, int level, int optname, const void *optval, socklen_t optlen) {  return 0;}; ;
 extern "C" int close(int s) {  return 0;}; 
extern "C" int connect(int s, const struct sockaddr *name, socklen_t namelen) {  return 0;}; 
extern "C" int listen(int s, int backlog) {  return 0;}; 
extern "C" ssize_t recv(int s, void *mem, size_t len, int flags) {  return 0;}; 
extern "C" ssize_t read(int s, void *mem, size_t len) {  return 0;}; 
extern "C" ssize_t readv(int s, const struct iovec *iov, int iovcnt) {  return 0;}; 
extern "C" ssize_t recvfrom(int s, void *mem, size_t len, int flags,
struct sockaddr *from, socklen_t *fromlen) {  return 0;}; 
extern "C" ssize_t send(int s, const void *dataptr, size_t size, int flags){  return 0;}; 
extern "C" ssize_t sendto(int s, const void *dataptr, size_t size, int flags,
sockaddr *to, socklen_t tolen){  return 0;}; 
extern "C" int socket(int domain, int type, int protocol){ 
  std::unique_ptr<esphome::socket::Socket> socket_ = esphome::socket::socket(domain, type, protocol);
    //static_cast<esphome::socket::Socket*>(ptr);
    if (socket_ == nullptr) {
    //ESP_LOGW(TAG, "Could not create socket");
   // return  reinterpret_cast<std::intptr_t>(socket_);
 
  }
  return (int) socket_.get();
}; 

extern "C" ssize_t write(int s, const void *dataptr, size_t size){  return 0;}; 
extern "C" ssize_t writev(int s, const struct iovec *iov, int iovcnt){  return 0;}; 
extern "C" int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                struct timeval *timeout){  return 0;}; 
              
              