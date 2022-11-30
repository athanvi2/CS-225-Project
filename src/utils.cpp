#include "utils.h"

std::vector<std::string> GetSubstrs(const std::string& str, char delimiter) {
  size_t last = 0;
  std::vector<std::string> substrs;
  for (size_t i = 0; i != str.length(); ++i) {
    if (str.at(i) == delimiter) {
      std::string substr = str.substr(last, i - last);
      last = i + 1;
      substrs.push_back(substr);
    }
  }
  std::string substr = str.substr(last, str.length() - last);
  substrs.push_back(substr);

  return substrs;
}

std::vector<std::vector<std::string>> CsvTwoD(const std::string& file) {
  std::ifstream ifs{file};
  std::vector<std::vector<std::string>> csv;
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> temp = GetSubstrs(line, ',');
    csv.push_back(temp);
  }
  return csv;
}