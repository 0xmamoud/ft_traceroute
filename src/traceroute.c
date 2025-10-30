#include "../includes/traceroute.h"

void print_help(void) {
  printf("Usage: ft_traceroute [OPTION...] HOST\n");
  printf("Print the route packets trace to network host.\n\n");
  printf("  -?, --help                 give this help list\n\n");
  printf("Report bugs to <bug-inetutils@gnu.org>.\n");
}
