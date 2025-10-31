# ft_traceroute

A simplified implementation of the `traceroute` network diagnostic tool in C.

## Description

`ft_traceroute` traces the route that packets take from your computer to a destination host across an IP network. It displays each hop (router) along the path and measures the round-trip time (RTT) for packets sent to each hop.

## How It Works

The program uses UDP packets with incrementing TTL (Time To Live) values:

1. Sends UDP packets with TTL=1, 2, 3, etc.
2. Each router decrements the TTL by 1
3. When TTL reaches 0, the router sends back an ICMP "Time Exceeded" message
4. Measures the round-trip time for each hop
5. Stops when the destination is reached

## Features

- Traces network path to any hostname or IP address
- Displays IP address and response time for each hop
- Sends 3 probes per hop for reliability
- Maximum 64 hops
- 5-second timeout per probe

## Requirements

- Linux/Unix system
- GCC compiler
- Root privileges (required for raw sockets)

## Installation

```bash
make
```

## Usage

```bash
sudo ./ft_traceroute <hostname>
```

### Examples

```bash
sudo ./ft_traceroute google.com
sudo ./ft_traceroute 8.8.8.8
```

### Help

```bash
./ft_traceroute --help
./ft_traceroute -?
```

## Output Format

```
traceroute to google.com (172.217.18.206), 64 hops max
  1   192.168.215.1  0.005ms  0.003ms  0.002ms
  2   192.168.139.1  0.002ms  0.002ms  0.002ms
  3   10.16.254.254  1.823ms  0.871ms  0.864ms
```

- Column 1: Hop number (TTL value)
- Column 2: IP address of the router
- Columns 3-5: Round-trip time for each of the 3 probes
- `*` indicates a timeout (no response)


### Network Protocols

- **UDP**: User Datagram Protocol for sending probes
- **ICMP**: Internet Control Message Protocol for receiving responses
- **Raw Sockets**: Required for custom packet handling

### Key Functions

- `send_probe()`: Sends a UDP packet with specified TTL
- `receive_icmp_reply()`: Receives ICMP response and measures RTT
- `run_traceroute()`: Main loop that orchestrates the tracing process

### Configuration

Default values (defined in `traceroute.h`):

- `MAX_HOPS`: 64 - Maximum number of hops
- `NPROBES`: 3 - Number of probes per hop
- `PORT`: 33434 - Starting UDP port number
- `MAX_WAIT_TIME`: 5 - Timeout in seconds
- `FIRST_TTL`: 1 - Starting TTL value

## Limitations

- IPv4 only (no IPv6 support)
- No advanced options (packet size, port selection, etc.)
- Requires root privileges

## License

This project is for educational purposes.
