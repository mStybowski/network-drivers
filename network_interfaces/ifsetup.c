#include <arpa/inet.h>
#include <linux/if.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int sfd;
  struct ifreq ifr;
  struct sockaddr_in* sin;

  sfd = socket(PF_INET, SOCK_DGRAM, 0);
  strncpy(ifr.ifr_name, argv[1], strlen(argv[1]) + 1);
  sin = (struct sockaddr_in*) &ifr.ifr_addr;
  memset(sin, 0, sizeof(struct sockaddr_in));
  sin->sin_family = AF_INET;
  sin->sin_port = 0;
  sin->sin_addr.s_addr = inet_addr(argv[2]);
  ioctl(sfd, SIOCSIFADDR, &ifr);
  ioctl(sfd, SIOCGIFFLAGS, &ifr);
  ifr.ifr_flags |= IFF_UP | IFF_RUNNING;
  ioctl(sfd, SIOCSIFFLAGS, &ifr);
  close(sfd);
  return EXIT_SUCCESS;
}
