#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../graph.h"
#include "../utils.h"
#include "../airport.h"


TEST_CASE("Invalid Airport Code (Calc Dist)") {
    std::string airport_one = '';
    std::string airport_two = 'zzz';
    double result = calcEdgeDistance(airport_one, airport_two);
    REQUIRE(result == -1);
}

TEST_CASE("Valid Airport Code (Calc Dist)") {
    std::string airport_one = 'GKA';
    std::string airport_two = 'MAG';
    double result = calcEdgeDistance(airport_one, airport_two);
    REQUIRE(int (result) == 107);
}


// Testing if entire grpah is correct