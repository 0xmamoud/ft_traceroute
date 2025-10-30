#include "../includes/traceroute.h"

int main(int argc, char **argv) {

  if (argc < 2 || argc > 3 || !is_valid_args(argc, argv)) {
    printf("Usage: %s <hostname>\n", argv[0]);
    return 1;
  }

  if (is_help(argc, argv) || argc < 2 || argc > 3) {
    print_help();
    return 0;
  }

  printf("hello world!\n");
  return 0;
}
