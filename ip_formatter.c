/*
 * =====================================================================================
 *
 *       Filename:  ip_formatter.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/08/2015 08:23:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dragan Glumac (DG), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>

void format_output(char *s1, char *s2) {
  printf("%-11s%15s\n", s1, s2);
}

int main() {
  struct ifaddrs *ifap;

  if (0 == getifaddrs(&ifap)) {
    struct ifaddrs *next = ifap;
    printf("\n");
    while (next != NULL) {
      if (next->ifa_addr->sa_family == AF_INET) {
        struct sockaddr_in *netmask = (struct sockaddr_in *) next->ifa_netmask;
        if (netmask != NULL) {
          struct sockaddr_in *subnet = malloc(sizeof(struct sockaddr_in)), 
                             *host = malloc(sizeof(struct sockaddr_in));
          format_output("Interface", next->ifa_name);
          printf("..........................\n");
          memcpy(subnet, next->ifa_addr, sizeof(struct sockaddr_in));
          subnet->sin_addr.s_addr &= netmask->sin_addr.s_addr;
          memcpy(host, next->ifa_addr, sizeof(struct sockaddr_in));
          host->sin_addr.s_addr &= ~(netmask->sin_addr.s_addr);
          format_output("IP addr is ",
              inet_ntoa(((struct sockaddr_in *)(next->ifa_addr))->sin_addr));
          format_output("host is ", inet_ntoa(host->sin_addr));
          format_output("subnet is ", inet_ntoa(subnet->sin_addr));
          printf("\n");
        }
      }
      next = next->ifa_next;
    }
    freeifaddrs(ifap);
  }

  return 0;
}
