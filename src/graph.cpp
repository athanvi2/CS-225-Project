#include "graph.h"

//Helper for pagerank adj
std::vector<std::vector<double>> adjWithDamping(std::vector<std::vector<double>> connections, double damping_factor) {
    double damping_factor_formula = (1 - damping_factor) / connections.size();

    for (unsigned i = 0; i < connections.size(); i++) {
        double sum = 0.0;
        for (unsigned j = 0; j < connections[i].size(); j++) {
            sum += connections[j][i];
        }
        if (sum == 0) {
            for (unsigned k = 0; k < connections.size(); k++) {
                connections[k][i] = 1/connections.size();
            }
        } else {
            for (unsigned l = 0; l < connections.size(); l++) {
                connections[l][i] = (connections[l][i] / sum) * damping_factor + damping_factor_formula;
            }
        }
    }
    return connections;
}

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
    connections.resize(adj_.size());
    for (unsigned i = 0; i < airports.size(); i++) adj_[i].resize(airports.size(),0.0);

    for (unsigned i = 0; i < adj_.size(); i++) connections[i].resize(adj_.size(),0.0);

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
        // generating pagerank adj matrix called connections
        for (unsigned row = 0; row < adj_.size(); row++) {
            for (unsigned col = 0; col < adj_.at(row).size(); col++) {
                double cell = adj_.at(row).at(col);
                if (cell != 0) connections.at(row).at(col) = 1.0;
                else connections.at(row).at(col) = 0.0;
            }
        }
    
    pagerank_adj = adjWithDamping(connections, 0.85);

}

/* BFS ALgorithm */
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

/* Dijkstra's Algorithm */
double Graph::Dijkstra(airport start, airport dest) {
    // will store distance, current airport, previous airport
    std::vector<std::pair<double, std::pair<airport, airport>>> queue;
    // current spot on the queue
    std::pair<double, std::pair<airport, airport>> minimum;
    int index = 0;
    airport temp;

    // populate the queue
    for (unsigned i = 0; i < airports.size(); i++) {
        if (airports[i].code == start.code) {
            queue.push_back(std::make_pair(0, std::make_pair(airports[i], temp)));
            minimum = queue[i];
        } else {
            queue.push_back(std::make_pair(INT_MAX, std::make_pair(airports[i], temp)));
        }
    }

    while (!queue.empty()) {
        // search for minimum distance on the queue
        for (unsigned i = 0; i < queue.size(); i++) {
            if (minimum.first >= queue[i].first) {
                minimum = queue[i];
                index = i;
            }
        }
        // remove minimum distance from the queue
        queue.erase(queue.begin()+index);
        // if minimum distance is the destination, returns shortest distance
        if (minimum.second.first.code == dest.code) {
            if (minimum.first == INT_MAX) {
                return -1;
            }
            return minimum.first;
        }
        // updates queue distances with shortest path (in terms of distance) for each node
        for (unsigned i = 0; i < minimum.second.first.connected.size(); i++) {
            if (minimum.second.first.connected[i].first.code != minimum.second.second.code) {
                airport curr_ap = airports.at(minimum.second.first.connected[i].first.index);
                for (unsigned j = 0; j < queue.size(); j++) {
                    if (queue[j].second.first.code == curr_ap.code) {
                        if (minimum.first  + minimum.second.first.connected[i].second < queue[j].first) {
                            queue[j].first = minimum.first +  minimum.second.first.connected[i].second;
                        }
                    }
                }
            }
        }
        minimum.first = INT_MAX;
    }
    return -1;
}

std::string Graph::getLeastStopsDistance(std::string airport_one, std::string airport_two) {
    airport ap_start = convertCodeToAirport(airport_one);
    airport ap_dest = convertCodeToAirport(airport_two);

    if (adj_.at(ap_start.index).at(ap_dest.index) != 0.0) return "Distance from " + airport_one + " to " + airport_two 
    + " based on least number of stops: " + std::to_string(calcEdgeDistance(airport_one, airport_two)) + " kilometers.";
    return "Distance from " + airport_one + " to " + airport_two + " based on least number of stops: " + std::to_string(BFS(ap_start, ap_dest)) + " kilometers";
}


std::string Graph::getShortestDistance(std::string airport_one, std::string airport_two) {
    airport ap_start = convertCodeToAirport(airport_one);
    airport ap_dest = convertCodeToAirport(airport_two);

    return "Distance from " + airport_one + " to " + airport_two + " based on shortest distance: " + std::to_string(Dijkstra(ap_start, ap_dest)) + " kilometers";
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
    airport ap;
    for (unsigned i = 0; i < airports.size(); i++) {
        if (airports.at(i).code == airport_code) ap = airports.at(i); 
    }
    return ap;
}

std::vector<double> Graph::PageRank(std::vector<std::vector<double>> pg_adj) {
    int iterations = 300;
    std::vector<double> init_guess(pg_adj.size(), 0);
    generate(init_guess.begin(), init_guess.end(), rand);
    
    std::vector<double> result = init_guess;
    std::vector<double> new_guess = init_guess;

    for (int iter = 0; iter < iterations; iter++) {
        for (unsigned i = 0; i < pg_adj.size(); i++) {
            result[i] = 0;
            for (unsigned j = 0; j < pg_adj[i].size(); j++) {
                result[i] += pg_adj[i][j] * new_guess[j];
            }
        }
        new_guess = result;
    }
    return new_guess;
}

std::vector<double> Graph::NormalizedPageRank(std::vector<double> new_guess) {
    std::vector<double> normalized_pr = new_guess;
    double norm = sqrt(inner_product(new_guess.begin(), new_guess.end(), new_guess.begin(), 0.0L));

    for (unsigned i = 0; i < new_guess.size(); i++) {
        normalized_pr[i] = new_guess[i] / norm;
    }
    return normalized_pr;
}

struct Compare {
    bool operator()(std::pair<double,int> a, std::pair<double, int> b) {
        return a.first < b.first;
    }
};

std::vector<std::string> Graph::PageRankResult(std::vector<double> normalized_pr, int top_nums) {
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, Compare> pq;

    for (unsigned i = 0; i < normalized_pr.size(); i++) {
        pq.push(std::make_pair(normalized_pr[i], i));
    }
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, Compare> printq;
    while (!pq.empty()) {
        std::cout << pq.top().first << " " << pq.top().second << std::endl;
        printq.push(pq.top());
        pq.pop();
    }
    std::vector<std::string> to_return;
    for (int i = 0; i < top_nums; i++) {

        to_return.push_back(airports[printq.top().second].name);
        printq.pop();
    }
    return to_return;
}

