#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int sfd, rc;
  char buf[128];

  struct sockaddr_in saddr; // Which is of the form:
            /*  struct sockaddr_in {
                 sa_family_t    sin_family; address family: AF_INET
                 in_port_t      sin_port;   port in network byte order
                 struct in_addr sin_addr;   internet address
                }; 
           */

              // Internet address 
           /*
           struct in_addr {
               uint32_t       s_addr;     // address in network byte order
           };
            */

  struct hostent* addrent;

  addrent = gethostbyname(argv[1]); // The gethostbyname() function returns a structure of type hostent for the given host name or IPv4 address

  // CREATING endpoint which returns file descriptor opened for process
  sfd = socket(PF_INET, SOCK_STREAM, 0); // 1. Indicating that we want to use internet IP protocole | 2. SOCK_STREAM for TCP and SOCK_DGRAM for UDP | 3. 0 indicates we want to use standard protocole for that socket that is ip (intenret protocole)

// SETTINGS OF saddr
  memset(&saddr, 0, sizeof(saddr)); // Filling saddr with zeros for a start
  saddr.sin_family = AF_INET; // Setting IP for protocole
  saddr.sin_port = htons(atoi(argv[2])); // Converts byte_order for host to network stanadrd needed for saddr.sin_port
  memcpy(&saddr.sin_addr.s_addr, addrent->h_addr, addrent->h_length); // Arrow operator allows to access properties of struct or union via pointer
// KONIEC SETOWANIA STRUKTURY saddr

  connect(sfd, (struct sockaddr*) &saddr, sizeof(saddr));
  // https://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html

  rc = read(sfd, buf, 128); // Reading 128 bytes from socket and transfering them to buffer. This function return the number of actuualy read bytes
  // https://pubs.opengroup.org/onlinepubs/009604599/functions/read.html

  write(1, buf, rc); // Reads rc-number of bytes from buffor to 1?
  // https://pubs.opengroup.org/onlinepubs/007904975/functions/write.html

  close(sfd);

  return EXIT_SUCCESS;
}
