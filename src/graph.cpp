#include "graph.h"

Graph::Graph(std::string airport_csv, std::string routes_csv) {
    // Reading into v2d
    std::vector<std::vector<std::string>> airports = CsvTwoD(airport_csv);
    std::vector<std::vector<std::string>> routes = CsvTwoD(routes_csv);

    // populate airports
    for (auto& ap : airports) {
        airport curr_airport;
        curr_airport = createAirport(ap);
        airports.push_back(curr_airport);
    }
}

int Graph::getDistance(std::string airport_one, std::string airport_two) {
    (void) airport_one;
    (void) airport_two;
    return 0;
}

airport Graph::createAirport(std::vector<std::string> line) {
    (void) line;
    airport ap;
    return ap;
}