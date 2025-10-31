#include "../includes/traceroute.h"

int main(int argc, char **argv) {

  t_config config = {0};

  if (argc < 2 || argc > 3 || !is_valid_args(argc, argv)) {
    printf("Usage: %s <hostname>\n", argv[0]);
    return 1;
  }

  if (is_help(argc, argv) || argc < 2 || argc > 3) {
    print_help();
    return 0;
  }

  if (resolve_hostname(argv[1], &config) != 0) {
    if (argc == 3 && resolve_hostname(argv[2], &config) != 0) {
      printf("traceroute: unknown host %s\n", argv[2]);
      return 1;
    } else if (argc < 3) {
      printf("traceroute: unknown host %s\n", argv[1]);
      return 1;
    }
  }

  config.udp_sockfd = create_udp_socket();
  if (config.udp_sockfd < 0) {
    perror("create_udp_socket");
    return 1;
  }
  config.icmp_sockfd = create_icmp_socket();
  if (config.icmp_sockfd < 0) {
    perror("create_icmp_socket");
    close(config.udp_sockfd);
    return 1;
  }

  printf("traceroute to %s (%s), %d hops max\n", config.hostname,
         config.ip_address, MAX_HOPS);

  run_traceroute(&config);

  close(config.udp_sockfd);
  close(config.icmp_sockfd);
  return 0;
}
