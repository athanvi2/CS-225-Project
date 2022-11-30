#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_map>

std::vector<std::string> GetSubstrs(const std::string& str, char delimiter);

std::vector<std::vector<std::string>> CsvTwoD(const std::string& file);