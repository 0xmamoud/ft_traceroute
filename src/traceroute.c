#include "../includes/traceroute.h"

void print_help(void) {
  printf("Usage: ft_traceroute [OPTION...] HOST\n");
  printf("Print the route packets trace to network host.\n\n");
  printf("  -?, --help                 give this help list\n\n");
  printf("Report bugs to <bug-inetutils@gnu.org>.\n");
}

void run_traceroute(t_config *config) {
  for (int ttl = FIRST_TTL; ttl <= MAX_HOPS; ttl++) {
    printf("%3d", ttl);
    bool addr_printed = false;
    bool reached_destination = false;

    for (int probe = 0; probe < NPROBES; probe++) {
      char reply_addr[INET_ADDRSTRLEN];
      double rtt;

      if (send_probe(config, ttl, probe) < 0) {
        printf(" *");
        continue;
      }

      if (receive_icmp_reply(config, reply_addr, &rtt) < 0) {
        printf(" *");
        continue;
      }

      if (!addr_printed) {
        printf("  %s  %.3fms", reply_addr, rtt);
        addr_printed = true;
      } else {
        printf("  %.3fms", rtt);
      }

      if (strcmp(reply_addr, config->ip_address) == 0) {
        reached_destination = true;
      }
    }

    printf("\n");

    if (reached_destination) {
      break;
    }
  }
}
