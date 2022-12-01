#pragma once
#include "utils.h"

struct airport {
    std::string name;
    std::string code;
    double latitude;
    double longitude;
    size_t index = 0;
    /* Map of airports that this airport is directly connected to; double = distance between airports */
    std::vector<std::pair<airport,double>> connected;
};