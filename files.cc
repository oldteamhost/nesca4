/*
 * NESCA 4
 * by oldteam & lomaster
 * license GPL-3.0
 *   Сделано от души 2023.
*/

#include "include/files.h"
#include <complex.h>

int get_count_lines(const char* path)
{
  int count = 0;
  std::ifstream file(path);
  std::string line;
  while (std::getline(file, line))
    ++count;
  return count;
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
