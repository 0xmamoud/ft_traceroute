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

  printf("hello world!\n");
  return 0;
}
