#include "../includes/traceroute.h"
#include <string.h>

int resolve_hostname(const char *hostname, t_config *config) {
  struct addrinfo hints, *res;
  struct sockaddr_in *addr_in;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_RAW;
  hints.ai_protocol = IPPROTO_ICMP;

  if (getaddrinfo(hostname, NULL, &hints, &res) != 0)
    return -1;

  addr_in = (struct sockaddr_in *)res->ai_addr;

  strncpy(config->hostname, hostname, sizeof(config->hostname) - 1);
  config->hostname[sizeof(config->hostname) - 1] = '\0';

  inet_ntop(AF_INET, &addr_in->sin_addr, config->ip_address, INET_ADDRSTRLEN);

  memcpy(&config->dest_addr, addr_in, sizeof(struct sockaddr_in));

  freeaddrinfo(res);

  return 0;
}

int create_icmp_socket() {
  int sockfd;

  sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sockfd == -1) {
    perror("socket");
    return -1;
  }

  struct timeval timeout;
  timeout.tv_sec = MAX_WAIT_TIME;
  timeout.tv_usec = 0;

  if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) ==
      -1) {
    perror("setsockopt");
    close(sockfd);
    return -1;
  }

  return sockfd;
}

int create_udp_socket(void) {
  int sockfd;

  sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (sockfd == -1) {
    perror("socket");
    return -1;
  }

  return sockfd;
}

int send_probe(t_config *config, int ttl, int seq) {
  char buf[40];
  struct sockaddr_in dest_addr;
  if (setsockopt(config->udp_sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) <
      0) {
    perror("setsockopt");
    return -1;
  }

  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(PORT + seq);
  dest_addr.sin_addr = config->dest_addr.sin_addr;

  memset(buf, 0, sizeof(buf));
  if (sendto(config->udp_sockfd, buf, sizeof(buf), 0,
             (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {
    perror("sendto");
    return -1;
  }

  return 0;
}

int receive_icmp_reply(t_config *config, char *reply_addr, double *rtt) {
  char buf[1024];
  struct sockaddr_in recv_addr;
  socklen_t recv_addr_len = sizeof(recv_addr);
  struct timeval tv_start, tv_end;

  gettimeofday(&tv_start, NULL);

  if (recvfrom(config->icmp_sockfd, buf, sizeof(buf), 0,
               (struct sockaddr *)&recv_addr, &recv_addr_len) < 0) {
    return -1;
  }

  gettimeofday(&tv_end, NULL);

  inet_ntop(AF_INET, &recv_addr.sin_addr, reply_addr, INET_ADDRSTRLEN);

  *rtt = (tv_end.tv_sec - tv_start.tv_sec) * 1000.0 +
         (tv_end.tv_usec - tv_start.tv_usec) / 1000.0;

  return 0;
}
