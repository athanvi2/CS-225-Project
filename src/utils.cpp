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
  
  std::string line;
  std::getline(ifs, line);
  for (std::string line; std::getline(ifs, line); line = "") {
    std::vector<std::string> temp = GetSubstrs(line, ',');
    // Remove last character if new line
    std::string last_word = temp.at(temp.size() - 1);
    if (!isalnum(last_word.at(last_word.size() - 1))) last_word.pop_back();
    temp.at(temp.size() - 1) = last_word;
    csv.push_back(temp);
  }

// for (unsigned i = 0; i < csv.size(); i++) {
//     for (unsigned j = 0; j < csv[i].size(); j++) {
//         std::cout << "   " << csv[i][j] << "    ";
//     }
//     std::cout << " "<< std::endl;
// }

  return csv;
}