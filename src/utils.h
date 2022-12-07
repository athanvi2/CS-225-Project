#pragma once
#include <utility>
#include <iostream>
#include <typeinfo>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <ctype.h>
#include <stdexcept>
#include <limits.h>
#include <stdio.h>

std::vector<std::string> GetSubstrs(const std::string& str, char delimiter);

std::vector<std::vector<std::string>> CsvTwoD(const std::string& file);