#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv) {
  socklen_t sl;
  int sfd, cfd, on = 1;
  struct sockaddr_in saddr, caddr;

// SETTINGS OF saddr
  memset(&saddr, 0, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(1234);

  sfd = socket(PF_INET, SOCK_STREAM, 0);

  setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*) &on, sizeof(on)); // The setsockopt() function shall set the option specified by the option_name , at the protocol level specified by the level argument, to the value pointed to by the option_value argument for the socket associated with the file descriptor specified by the socket argument.
  //            SO_REUSEADDR 
  //            Indicates that the rules used in validating addresses
  //            supplied in a bind(2) call should allow reuse of local
  //            addresses.  For AF_INET sockets this means that a socket
  //            may bind, except when there is an active listening socket
  //            bound to the address.  When the listening socket is bound
  //            to INADDR_ANY with a specific port then it is not possible
  //            to bind to this port for any local address.  Argument is
  //            an integer boolean flag
  // https://pubs.opengroup.org/onlinepubs/000095399/functions/setsockopt.html
  // https://man7.org/linux/man-pages/man7/socket.7.html

  bind(sfd, (struct sockaddr*) &saddr, sizeof(saddr));
  //   When a socket is created with socket(), it exists in a name
  //     space (address family) but has no address assigned to it.  bind()
  //     assigns the address specified by addr to the socket referred to
  //     by the file descriptor sockfd.  addrlen specifies the size, in
  //     bytes, of the address structure pointed to by addr.
  //     Traditionally, this operation is called “assigning a name to a
  //     socket”.

  listen(sfd, 5);

  while(1) {
    memset(&caddr, 0, sizeof(caddr));
    sl = sizeof(caddr);
    cfd = accept(sfd, (struct sockaddr*) &caddr, &sl);
    write(cfd, "Hello World!\n", 14);
    sleep(1200);
    close(cfd);
  }
  close(sfd);
  return EXIT_SUCCESS;
}
