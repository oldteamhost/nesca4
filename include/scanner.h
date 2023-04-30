#include <iostream>
#include <vector>

// main scan
int tcp_scan_port(const char *ip, int port, int timeout_ms);
// dns scan
int dns_scan(std::string domain, std::string domain_1level);
