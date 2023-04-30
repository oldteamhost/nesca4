#include <vector>
#include <iostream>

// get now tim
const char* get_time();
// custom delay
void delay_ms(int milliseconds);
// check ansii colors
bool check_ansi_support(void);
// write ports
std::vector<int> write_ports(std::string mode);
// print help menu
void logo(void);
