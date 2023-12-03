/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "../include/nescautils.h"

bool hikvision_screenshot(const std::string& ip, const long user_id, const NET_DVR_DEVICEINFO_V40 device, const std::string& path)
{
  for (int channel = 0; channel < device.struDeviceV30.byChanNum; channel++) {
    std::string filename = path + ip + "_" + std::to_string(channel) + ".jpg";
    char screenshotFilenameBuffer[256];
    strcpy(screenshotFilenameBuffer, filename.c_str());

    NET_DVR_JPEGPARA params = {0};
    params.wPicQuality = 2;
    params.wPicSize = 0;

    if (NET_DVR_CaptureJPEGPicture(user_id, channel, &params, screenshotFilenameBuffer))
      return true;
  }

  return false;
}

std::map<int,std::string> services_nesca::parse_services(const std::string& filename)
{
  std::map<int, std::string> result;
  std::ifstream file(filename);

  if (!file)
    return result;

  std::string line;

  while (std::getline(file, line)) {
    std::istringstream lineIss(line);
    int key;
    std::string value;
    if (lineIss >> value >> key)
      result[key] = value;
  }

  file.close();
  return result;
}

std::string services_nesca::probe_service(int port)
{
  const std::string service = data[port];
  if (service.empty())
    return "N/A";

  return data[port];
}

void services_nesca::init_services(void)
{
  data = parse_services("./resources/nesca-services");
}

std::unordered_map<std::string, std::string>
get_negatives(const std::string& file_path)
{
  std::unordered_map<std::string, std::string> res;
  std::string line, value, type;

  std::ifstream file(file_path);
  while (std::getline(file, line)) {
    if (line.empty() || line.substr(0, 2) == "##")
      continue;

    std::stringstream ss(line);

    if (std::getline(ss, value, '|') && std::getline(ss, type)) {
      value = value.substr(value.find_first_not_of(' '));
      value = value.substr(0, value.find_last_not_of(' ') + 1);

      type = type.substr(type.find_first_not_of(' '));
      type = type.substr(0, type.find_last_not_of(' ') + 1);
      res[value] = type;
    }
  }

  file.close();
  return res;
}

bool check_ansi_support(void)
{
  const char* envValue = std::getenv("TERM");
  if (envValue == nullptr)
    return false;

  return std::string(envValue).find("xterm") != std::string::npos;
}

std::vector<int> write_ports(std::string mode)
{
  std::vector<int> temp;
  std::transform(mode.begin(), mode.end(), mode.begin(), [](unsigned char c) {
    return std::tolower(c);
  });

  if (mode == "all"){
    for (int i = 0; i < 65536; i++) {temp.push_back(i);}
    return temp;
  }
  else if (mode == "nesca" || mode == "nesca3"){
    /*On https://github.com/cora32/Nesca/blob/master/resource.h*/
    temp = {80,81,88,8080,8081,60001,60002,8008,8888,554,9000,441,4111,6667,3536,22,21};

    return temp;
  }
  else if (mode == "top100"){
    temp = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080,
       1723, 111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81,
       6001, 10000, 514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001,
       1027, 49152, 2049, 1028, 1029, 5901, 32768, 1434, 3283, 5800, 389, 53, 17988,
       106, 5666, 1725, 465, 995, 548, 7, 123, 389, 113, 37, 427, 8001, 427, 1726,
       49153, 2002, 515, 1030, 1031, 1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
       1040, 1041, 1042, 1043, 1044, 1045, 1046, 1047, 1048, 1049, 1050, 1051, 1052,
       1053, 1054, 1055, 1056, 1057, 1058, 1059, 1060, 1061, 1062, 1063, 1064, 1065,
       1066, 1067, 1068, 1069, 1070, 1071, 1072, 1073, 1074, 1075, 1076, 1077};

      return temp;
  }
  else if (mode == "top50"){
    temp  = {80, 443, 22, 21, 25, 3389, 110, 143, 53, 445, 139, 3306, 8080, 1723,
      111, 995, 993, 5900, 1025, 587, 8888, 199, 1720, 465, 548, 113, 81, 6001, 10000,
      514, 5060, 179, 1026, 23, 8443, 8000, 444, 1433, 1900, 2001, 1027, 49152,
      2049, 1028, 1029, 5901, 32768, 1434, 3283}; 
    return temp;
  }
  else if (mode == "http"){
    temp = {80,81,8080,8081,8888, 8008};
    return temp;
  }
  else if (mode == "nesca4"){
    temp = {80,81,8080,8081,8888,8008,21,22,8000,37777};
    return temp;
  }

  return {-1};
}

void logo(void)
{
  puts("d8b   db d88888b .d8888.  .o88b.  .d8b.         j88D  ");
  puts("888o  88 88'     88'  YP d8P  Y8 d8' `8b       j8~88  "); 
  puts("88V8o 88 88ooooo `8bo.   8P      88ooo88      j8' 88  ");
  puts("88 V8o88 88~~~~~   `Y8b. 8b      88~~~88      V88888D ");
  puts("88  V888 88.     db   8D Y8b  d8 88   88          88  ");
  puts("VP   V8P Y88888P `8888Y'  `Y88P' YP   YP          VP  \n");
}

std::vector<int> parse_range(const std::string& range_string)
{
  std::vector<int> result;
  int start = 0, end = 0;
  bool found_dash = false;
  for (char c : range_string) {
    if (c == '-') {
      found_dash = true;
      start = std::stoi(range_string.substr(0, end));
      end = std::stoi(range_string.substr(end + 1));
    }
    ++end;
  }

  if (!found_dash)
    return result;

  for (int i = start; i <= end; ++i)
    result.push_back(i);

  return result;
}

bool __check_root_perms()
{
  return (geteuid() == 0);
}

int write_temp(const std::string& data, const std::string& file_name)
{
  const std::vector<std::string> temp = write_file(file_name);
  for (auto& str : temp)
    if (str == data)
      return -1;

  if (temp.size() > 2000){
    std::filesystem::path file_path(file_name);
    std::filesystem::remove(file_path);
  }
  const int write = write_line(file_name, data + "\n");
  if (write != 0)
    return -1;

  return 0;
}

std::string parse_word(const std::vector<std::string>& options,
    const std::string& search_word)
{
  for (const std::string& option : options)
    if (option == search_word)
      return option;

  return "failed";
}

std::string to_lower_case(std::string str)
{
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {return std::tolower(c);});
  return str;
}

size_t find_char(const std::string& str, char ch)
{
  return str.find(ch);
}

int get_count_lines(const char* path)
{
  int len = 0;

  std::ifstream file(path);
  std::string line;
  while (std::getline(file, line))
    ++len;

  return len;
}

bool check_file(const char* path)
{
  std::ifstream file(path);
  return file.good();
}

std::vector<std::string> write_file(const std::string& filename)
{
  std::vector<std::string> lines;
  std::string line;

  std::ifstream file(filename);
  if (file.fail())
    return {"-1"};

  while (std::getline(file, line))
    lines.push_back(line);

  return lines;
}

int write_line(std::string path, std::string line)
{
  std::ofstream outfile;

  outfile.open(path, std::ios_base::app);
  if (!outfile.is_open())
    return -1;

  outfile << line;
  outfile.close();

  return 0;
}

int delete_line_from_file(const std::string& filename, const std::string& line_to_delete)
{
  std::vector<std::string> lines;
  std::string line;

  std::ifstream input_file(filename);
  if (!input_file)
    return -1;

  while (std::getline(input_file, line))
    lines.push_back(line);

  input_file.close();

  auto it = std::find(lines.begin(), lines.end(), line_to_delete);
  if (it == lines.end())
    return -1;

  lines.erase(it);

  std::ofstream output_file(filename);
  if (!output_file)
    return -1;

  for (const auto& updated_line : lines)
    output_file << updated_line << std::endl;

  output_file.close();
  return 0;
}
#include "../config/nescaopts.h"
std::string gettypeddos(class arguments_program& argp)
{
  if (argp.ip_ddos)
    return "ip-empty";
  if (argp.tcp_ddos)
    return "tcp";
  if (argp.icmp_ddos)
    return "icmp";
  if (argp.udp_ddos)
    return "udp";

  return "n/a";
}
