#include "utils.h"

std::string file_to_string(const std::string& filename) {
  std::ifstream text(filename);

  std::stringstream strStream;c
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

//////////

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

//////////

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

//////////

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

//////////

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}

//////////

std::vector<std::vector<std::string>> file_to_V2D(const std::string & filename) {
    std::vector<std::string> rows;
    SplitString(file_to_string(filename), '\n', rows);

    std::vector<std::vector<std::string>> v2d;
    for (auto row : rows) {
        std::vector<std::string> curr_row;
        SplitString(row, ',', curr_row);
        v2d.push_back(curr_row);
    }
    for (auto& row : v2d) {
        for (auto& entry : row) entry = Trim(entry);
    }
    return v2d;
}