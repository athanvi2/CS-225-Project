#include "utils.h"

struct airport {
    std::string name;
    std::string code;
    double latitude;
    double longitude;
    /* Map of airports that this airport is directly connected to; double = distance between airports */
    std::map<airport, double> connected;
};