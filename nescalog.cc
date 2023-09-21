/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/nescalog.h"
#include "ncbase/include/json.h"
#include "ncsock/include/strbase.h"
#include "ncsock/include/base.h"
#include <cstdio>
#include <cstring>

html_output hou;

std::string
nesca_prints::html_to_ansi_color(const std::string& html_color)
{
  if (html_color.size() != 7 || html_color[0] != '#') {return "";}
  std::istringstream stream(html_color.substr(1));

  /* Преобразуем значения к диапазону [0, 255] */
  int r = std::stoi(html_color.substr(1, 2), nullptr, 16);
  int g = std::stoi(html_color.substr(3, 2), nullptr, 16);
  int b = std::stoi(html_color.substr(5, 2), nullptr, 16);

  return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string
nesca_prints::main_nesca_out(const std::string& opt, const std::string& result, const int mode, const std::string& opt1, const std::string& opt2,
                            const std::string& result1, const std::string& result2, const std::string& rtt,
                            std::string type, std::string protocol)
{
  std::string temp, temp_file;
  char dots[3] =
  {':', ':', ':'};

  if (opt.empty())  {dots[0] = ' '; }
  if (opt1.empty()) {dots[1] = ' ';}
  if (opt2.empty()) {dots[2] = ' ';}

  if (mode == 0) {
    temp = green_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 1) {
    temp = red_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 2) {
    temp = yellow_html + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + result + reset_color;
      temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[1] + result;
  }
  else if (mode == 3) {
    temp = gray_nesca + "[>][" + opt + "]" + dots[0] + reset_color +
      sea_green + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      golder_rod + result2 + reset_color;

    temp_file = "[>][" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

    if (html_save) {hou.html_add_result(html_file_path,get_time(), result, result, "RTT", rtt+"ms", opt2, result2, opt1, result1, "SERVICE", protocol);}
  }
  else if (mode == 4) {
    temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
      golder_rod + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      golder_rod + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      golder_rod + result2 + reset_color;

    temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;
  }
  else if (mode == 5) {
    temp = gray_nesca + print_get_time(get_time()) + "[" + opt + "]" + dots[0] + reset_color +
      green_html + result + reset_color + gray_nesca + " " + opt1 + dots[1] + " " + reset_color +
      green_html + result1 + reset_color + gray_nesca + " " + opt2 + dots[2] + " " + reset_color +
      green_html + result2 + reset_color;

    temp_file = print_get_time(get_time()) + "[" + opt + "]" + dots[0] +
      result + " " + opt1 + dots[1] + " " + result1 + " " + opt2 + dots[2] + " " + result2;

  }
  else if (mode == 6) {
    temp = golder_rod + "-> " + result + " " + opt + " " + result1;
      temp_file = "-> " + result + " " + opt + " " + result1;

  }

  return temp;
}
void
nesca_prints::nlog_packet_trace(std::string action, std::string protocol, std::string& source_ip,
      std::string& dest_ip, int source_port, int dest_port,
      std::string message, int ttl, int id, int win,
      int seq, int iplen)
{
  /*Ужас но подругому не сделать.*/
  const std::string temp = green_html + "-> " + reset_color +
      green_html + "  " + action + reset_color + green_html + "  " + protocol + "  " + reset_color +
      green_html + source_ip + ":" + std::to_string(source_port) + " > " + dest_ip + ":" +
      std::to_string(dest_port) + reset_color + golder_rod + message + reset_color +
      gray_nesca + "  TTL  " + golder_rod + std::to_string(ttl) + gray_nesca + "  ID  " + golder_rod +
      std::to_string(id) + gray_nesca + "  WINDOW  " + golder_rod + std::to_string(win) + gray_nesca +
      "  IPLEN  " + golder_rod + std::to_string(iplen) + gray_nesca + "  SEQ  " + golder_rod + std::to_string(seq) +reset_color;

  fwrite(temp.c_str(), sizeof(char), strlen(temp.c_str()), stdout);
}

void
nesca_prints::disable_colors(void)
{
  colors = false;
  gray_nesca = "";
  golder_rod = "";
  sea_green = "";
  green_html = "";
  red_html = "";
  yellow_html = "";
  reset_color = "";
}

std::string
nesca_prints::print_get_time(const char* time)
{
  const std::string temp = "[" + std::string(time) + "]";
  return temp;
}

int
nesca_prints::import_color_scheme(const std::string& file_name, std::map<std::string, std::string>& config_values)
{
  std::ifstream configFile(file_name);
  if (configFile.is_open()){
    std::string line;
    while (std::getline(configFile, line)){
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos){
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        config_values[key] = value;
      }
    }
    return 0;
  }
  return -1;
}

void
nesca_prints::golder_rod_on(void) {
  fwrite(golder_rod.c_str(), sizeof(char), strlen(golder_rod.c_str()), stdout);
}

void
nesca_prints::sea_green_on(void) {
  fwrite(sea_green.c_str(), sizeof(char), strlen(sea_green.c_str()), stdout);
}

void
nesca_prints::reset_colors(void) {
  fwrite(reset_color.c_str(), sizeof(char), strlen(reset_color.c_str()), stdout);
}

void
nesca_prints::gray_nesca_on(void) {
  fwrite(gray_nesca.c_str(), sizeof(char), strlen(gray_nesca.c_str()), stdout);
}

void
nesca_prints::yellow_html_on(void) {
  fwrite(yellow_html.c_str(), sizeof(char), strlen(yellow_html.c_str()), stdout);
}

void
nesca_prints::green_html_on(void) {
  fwrite(green_html.c_str(), sizeof(char), strlen(green_html.c_str()), stdout);
}

void
nesca_prints::red_html_on(void) {
  fwrite(red_html.c_str(), sizeof(char), strlen(red_html.c_str()), stdout);
}

void
nesca_prints::custom_color_on(const std::string& html_color)
{
  if (colors == true) {std::cout << html_to_ansi_color(html_color);}
}

int
nesca_prints::processing_color_scheme(const std::map<std::string, std::string>& config_values)
{
  for (const auto& kvp : config_values) {
    if (kvp.first == "auth") {
      gray_nesca = html_to_ansi_color(kvp.second);
    }
    else if (kvp.first == "title") {
      golder_rod = html_to_ansi_color(kvp.second);
    }
    else if (kvp.first == "link") {
      sea_green = html_to_ansi_color(kvp.second);
    }
    else if (kvp.first == "ok") {
      green_html = html_to_ansi_color(kvp.second);
    }
    else if (kvp.first == "error") {
      red_html = html_to_ansi_color(kvp.second);
    }
    else if (kvp.first == "debug") {
      yellow_html = html_to_ansi_color(kvp.second);
    }
  }
  return 0;
}

void
nesca_prints::nlog_trivial(const std::string& message)
{
  std::string log = print_get_time(get_time()) + "[OK]:" + message;
  fprintf(stdout, "%s%s", green_html.c_str(), log.c_str()); 
}

void
nesca_prints::nlog_error(const std::string& message)
{
  const std::string log = print_get_time(get_time()) + "[ERROR]:" + message;
  fprintf(stdout, "%s%s", red_html.c_str(), log.c_str()); 
}

void
nesca_prints::nlog_custom(const std::string& auth, std::string message, int color)
{
  const std::string log = print_get_time(get_time()) + "[" + auth + "]:" + message;

  if      (color == 0) {green_html_on();}
  else if (color == 1) {yellow_html_on();}
  else if (color == 2) {red_html_on();}

  fwrite(log.c_str(), sizeof(char), strlen(log.c_str()), stdout);
}
