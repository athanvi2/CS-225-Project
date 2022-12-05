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
        airport start_airport = convertCodeToAirport(route.at(1));
        airport dest_airport = convertCodeToAirport(route.at(2));
        routes.push_back(std::make_pair(start_airport, dest_airport));
    }

    // resize adj_
    adj_.resize(airports.size());
    for (unsigned i = 0; i < airports.size(); i++) adj_[i].resize(airports.size(),0.0);

    // populate adj_ matrix with values
    for (unsigned i = 0; i < routes.size(); i++) {
        double dist = calcEdgeDistance(routes[i].first.code, routes[i].second.code);
        adj_.at(routes[i].first.index).at(routes[i].second.index) = dist;
        adj_.at(routes[i].second.index).at(routes[i].first.index) = dist;

        routes[i].first.connected.push_back(std::make_pair(routes[i].second, dist));
        routes[i].second.connected.push_back(std::make_pair(routes[i].first, dist));

        airports.at(routes[i].first.index).connected.push_back(std::make_pair(routes[i].second, dist));
        airports.at(routes[i].second.index).connected.push_back(std::make_pair(routes[i].first, dist));
    }
}

double Graph::BFS(airport start, airport dest) {
    std::queue<std::pair<airport, airport>> visited;

    // Resize and populate visited nodes
    std::vector<std::pair<airport, bool>> airports_visited;
    // 0 - not visited, 1 - discovery, 2 - cross 
    // Generate BFS's Adjacency Matrix
    std::vector<std::vector<std::pair<double,int>>> bfs_adj;
    bfs_adj.resize(airports.size());
    for (unsigned i = 0; i < airports.size(); i++) {
        bfs_adj[i].resize(airports.size());
        airports_visited.push_back(std::make_pair(airports.at(i), false));
    }
    for (unsigned row = 0; row < bfs_adj.size(); row++) {
        for (unsigned col = 0; col < bfs_adj[row].size(); col++) {
            bfs_adj[row][col] = std::make_pair(adj_[row][col], 0);
        }
    }

    // Populating bfs_adj
    airports_visited.at(start.index).second = true;
    for (unsigned i = 0; i < start.connected.size(); i++) {
        airport next_airport = airports.at(start.connected[i].first.index);
        std::pair<airport, airport> edge = std::make_pair(start,next_airport);
        visited.push(edge);
        airports_visited.at(next_airport.index).second = true;
        bfs_adj[edge.first.index][edge.second.index].second = 1;
    }
    while (!visited.empty() && airports_visited.at(dest.index).second == false) {
        std::pair<airport, airport> curr_edge = visited.front();
        visited.pop();
        airport dest_airport = airports.at(curr_edge.second.index);
        for (unsigned i = 0; i < dest_airport.connected.size(); i++) {
            if (airports_visited.at(dest_airport.connected[i].first.index).second == false) {
                airport next_airport = airports.at(dest_airport.connected[i].first.index);
                std::pair<airport, airport> edge = std::make_pair(dest_airport, next_airport);
                visited.push(edge);
                airports_visited.at(next_airport.index).second = true;
                bfs_adj[edge.first.index][edge.second.index].second = 1;
            }
        }
    }

    // Calc distance 
    if (visited.empty()) return -1;
    return backTrack(start, dest, bfs_adj);
}

double Graph::backTrack(airport start, airport dest, std::vector<std::vector<std::pair<double,int>>> bfs_adj) {
    double total_distance = 0.0;
    while (start.code != dest.code) {
        for (unsigned i = 0; i < bfs_adj.size(); i++) {
            if (bfs_adj[i][dest.index].second == 1) {
                total_distance += bfs_adj[i][dest.index].first;
                dest = airports.at(i);
            }
        }
    }
    return total_distance;
}



/**
 * 1) If an edge is already marked 1 or 2, then don't add it to the queue
    - bfs_adj[edge.first.first.index][edge.first.second.index].second == 0 or 1 or 2
        - bfs_adj's Row x Col --> cell that has (double, int) --> (distance, status of edge 0,1,2)
    - If == 1 or 2, skip
 * 2) If the node that this edge connects to is 
 * .   a) Visited: Mark this edge as cross
            - If airports_visited.at(destination_airport.index).second = true
            - bfs_adj[edge.first.first.index][edge.first.second.index].second == 2
 *     b) Not Visited: Mark this edge as discovery, Mark this node as visited, add destination airport to queue, redo process for this node
            - If airports_visited.at(destination_airport.index).second = false
            - bfs_adj[edge.first.first.index][edge.first.second.index].second == 1
            - airports_visited.at(destination_airport.index).second = true
            - Make the route, make <route,status>, add this edge to queue
 */

double Graph::getDistance(std::string airport_one, std::string airport_two) {
    airport ap_start = convertCodeToAirport(airport_one);
    airport ap_dest = convertCodeToAirport(airport_two);

    if (adj_.at(ap_start.index).at(ap_dest.index) != 0.0) return calcEdgeDistance(airport_one, airport_two);
    return BFS(ap_start, ap_dest);
}

double Graph::calcEdgeDistance(std::string airport_one, std::string airport_two) {
    // Finding airport that this string represents
    airport first_ap; airport second_ap;
    for (airport ap : airports) {
        if (ap.code == airport_one) first_ap = ap;
        if (ap.code == airport_two) second_ap = ap;
    }

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

    ap.name = line.at(1);
    ap.code = line.at(2);

    ap.latitude = std::stod(line.at(3));
    ap.longitude = std::stod(line.at(4));
    return ap;
}

airport Graph::convertCodeToAirport(std::string airport_code) {
    airport ap = airports.at(0);
    for (unsigned i = 0; i < airports.size(); i++) {
        if (airports.at(i).code == airport_code) ap = airports.at(i);
    }
    return ap;
    
}