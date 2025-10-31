#ifndef FT_TRACEROUTE_H
#define FT_TRACEROUTE_H

#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_HOPS 30
#define NPROBES 3
#define PORT 33434
#define MAX_WAIT_TIME 5
#define FIRST_TTL 1

typedef struct s_config {
  char hostname[256];
  char ip_address[INET_ADDRSTRLEN];
  struct sockaddr_in dest_addr;
  int udp_sockfd;
  int icmp_sockfd;
} t_config;

bool is_help(int argc, char **argv);
bool is_valid_args(int argc, char **argv);
char *get_hostname(int argc, char **argv);

int resolve_hostname(const char *hostname, t_config *config);
void print_help();

int create_icmp_socket();
int create_udp_socket();

#endif
