#include "graph.h"

Graph::Graph(std::string airport_csv, std::string routes_csv) {
    // reading into v2d
    std::vector<std::vector<std::string>> airports_vect = CsvTwoD(airport_csv);
    std::vector<std::vector<std::string>> routes_vect = CsvTwoD(routes_csv);

    // populate airports
    for (unsigned i = 0; i < airports_vect.size(); i++) {
        airport curr_airport = createAirport(airports_vect[i]);
        curr_airport.index = i;
        airports.push_back(curr_airport);
    }

    // populate routes
    for (auto& route : routes_vect) {
        airport start_airport = convertCodeToAirport(route.at(0));
        airport dest_airport = convertCodeToAirport(route.at(1));
        routes.push_back(std::make_pair(start_airport, dest_airport));
    }

    // resize adj_
    adj_.resize(airports.size());
    for (unsigned i = 0; i < airports.size(); i++) adj_[i].resize(airports.size(), 0.0);

    // populate adj_ matrix with values
    for (std::pair<airport, airport>& edge : routes) {
        double dist = calcEdgeDistance(edge.first.code, edge.second.code);
        adj_.at(edge.first.index).at(edge.second.index) = dist;
        adj_.at(edge.second.index).at(edge.first.index) = dist;
    }

}

//@TODO - AFTER BFS IMPLEMENTING
double Graph::getDistance(std::string airport_one, std::string airport_two) {
    airport airport_1 = convertCodeToAirport(airport_one);
    airport airport_2 = convertCodeToAirport(airport_two);
    if (adj_.at(airport_1.index).at(airport_2.index) != 0.0) return calcEdgeDistance(airport_one, airport_two);
    // CALL BFS
}

double Graph::calcEdgeDistance(std::string airport_one, std::string airport_two) {
    // Finding airport that this string represents
    airport first_ap; airport second_ap;
    for (airport ap : airports) {
        if (ap.code == airport_one) first_ap = ap;
        if (ap.code == airport_two) second_ap = ap;
    }
    // Checking for invalid aiport_name entries
    if (first_ap.code == "" || second_ap.code == "") return -1.0; 

    // Calculating Distance
    double lat1 = first_ap.latitude; double lat2 = second_ap.latitude;
    double lon1 = first_ap.longitude; double lon2 = second_ap.longitude;

    double radius = 6371000;
    double phi1 = lat1 * M_PI/180;
    double phi2 = lat2 * M_PI/180;
    double deltaPhi = (lat2 - lat1) * M_PI/180;
    double deltaLambda = (lon2 - lon1) * M_PI/180;

    double a = ( sin(deltaPhi/2)*sin(deltaPhi/2) ) + cos(phi1) * cos(phi2) * ( sin(deltaLambda/2)*sin(deltaLambda/2) );
    double c = 2 * atan2(sqrt(a), sqrt((1-a)));
    double d = radius * c;

    return d/1000;
}

airport Graph::createAirport(std::vector<std::string> line) {
    airport ap;

    ap.name = line.at(0);
    ap.code = line.at(1);
    
    // std::cout << "FIRST: " << line.at(2) << "   SECOND: " << line.at(3) << std::endl;

    ap.latitude = std::stod(line.at(2));
    ap.longitude = std::stod(line.at(3));
    return ap;
}

airport Graph::convertCodeToAirport(std::string airport_code) {
    airport ap;
    for (unsigned i = 0; i < airports.size(); i++) {
        if (airports.at(i).code == airport_code) ap = airports.at(i);
    }
    return ap;
    
}