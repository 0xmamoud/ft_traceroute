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

bool is_help(int argc, char **argv);
bool is_valid_args(int argc, char **argv);
char *get_hostname(int argc, char **argv);

void print_help();

#endif
