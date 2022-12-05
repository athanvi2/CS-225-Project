#include "graph.h"

Graph::Graph(std::string airport_csv, std::string routes_csv) {
    // reading into v2d
    std::vector<std::vector<std::string>> airports_vect = CsvTwoD(airport_csv);
    std::vector<std::vector<std::string>> routes_vect = CsvTwoD(routes_csv);

//     for (unsigned i = 0; i < routes_vect.size(); i++)
//         {
//     for (unsigned j = 0; j < routes_vect[i].size(); j++)
//         {
//         std::cout << "   " << routes_vect[i][j] << "    ";
//     }
//     std::cout << " "<< std::endl;
// }

// for (unsigned i = 0; i < airports_vect.size(); i++)
//         {
//     for (unsigned j = 0; j < airports_vect[i].size(); j++)
//         {
//         std::cout << "   " << airports_vect[i][j] << "    ";
//     }
//     std::cout << " "<< std::endl;
// }

    // populate airports
    for (unsigned i = 0; i < airports_vect.size(); i++) {
        airport curr_airport = createAirport(airports_vect[i]);
        curr_airport.index = i;
        airports.push_back(curr_airport);
    }

    // populate routes
    for (auto& route : routes_vect) {
        // std::cout << "Route inner vector: " << std::endl;
        // for (unsigned i = 0; i < route.size(); i++) std::cout << route[i] << " ";
        // std::cout << std::endl;
        // std::cout << "Route[1]: " << route.at(1) << "  " << "Route[2]: " << "_" << route.at(2) << "_" << std::endl;
        airport start_airport = convertCodeToAirport(route.at(1));
        airport dest_airport = convertCodeToAirport(route.at(2));
        // std::cout << start_airport.code << "!"<< dest_airport.code << std::endl;
        routes.push_back(std::make_pair(start_airport, dest_airport));
    }

    // for (unsigned i = 0; i < routes.size(); i++) {
    //    std::cout << routes[i].first.code << "?" << routes[i].second.code << std::endl;
    // }



    // resize adj_
    adj_.resize(airports.size());
    for (unsigned i = 0; i < airports.size(); i++) adj_[i].resize(airports.size(),0.0);

    // populate adj_ matrix with values
    for (unsigned i = 0; i < routes.size(); i++) {
        double dist = calcEdgeDistance(routes[i].first.code, routes[i].second.code);
        adj_.at(routes[i].first.index).at(routes[i].second.index) = dist;
        adj_.at(routes[i].second.index).at(routes[i].first.index) = dist;

        // std::cout << "Matrix at [" << routes[i].first.index << "][" << routes[i].second.index << "]: " << adj_.at(routes[i].first.index).at(routes[i].second.index) << std::endl;
        // std::cout << "Above line should be: " << dist << std::endl;

        routes[i].first.connected.push_back(std::make_pair(routes[i].second, dist));
        routes[i].second.connected.push_back(std::make_pair(routes[i].first, dist));

        airports.at(routes[i].first.index).connected.push_back(std::make_pair(routes[i].second, dist));
        airports.at(routes[i].second.index).connected.push_back(std::make_pair(routes[i].first, dist));
        // std::cout << "hi " << adj_[1][0] << std::endl;

        // std::cout << (adj_.at(routes[i].first.index).at(routes[i].second.index) == dist) << std::endl;
    }



//     std::cout << count << std::endl;

//     for (unsigned i = 0; i < routes.size(); i++) {
//         std::cout << routes[i].first.code << "&" << routes[i].second.code << std::endl;
//     }


   
    // for (unsigned j = 0; j < routes[1].first.connected.size(); j++) {
    //     std::cout << routes[1].first.name << " " << routes[1].first.connected[j].first.code << "&" << routes[1].first.connected[j].second << std::endl;
    // }


    for (unsigned i = 0; i < airports.size(); i++) {
         std::cout << airports[i].connected.size() << std::endl;
        for (unsigned j = 0; j < airports[i].connected.size(); j++) {
            std::cout << airports[i].name << "  " << airports[i].connected[j].first.name << "  " << airports[i].connected[j].second << std::endl;
        }
    }




    // for (unsigned i = 0; i < adj_.size(); i++) {
    // for (unsigned j = 0; j < adj_[i].size(); j++) {
    //     std::cout << "   " << adj_[i][j] << "    ";
    //     }
    // std::cout << " "<< std::endl;
    // }



}
double Graph::BFS(airport start, airport dest) {
    std::queue<std::pair<std::pair<airport, airport>,int>> visited;


    // Resize and populate visited nodes
    std::vector<std::pair<airport, bool>> airports_visited;
    airports_visited.resize(airports.size());

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
    for (unsigned i = 0; i < start.connected.size(); i++) {
        std::pair<airport, airport> route = std::make_pair(start,start.connected[i].first);
        std::pair<std::pair<airport, airport>, int> edge = std::make_pair(route, 0);
        visited.push(edge);
    }
    airports_visited.at(start.index).second = true;
    while (!visited.empty() && airports_visited.at(dest.index).second == false) {
        // @Todo: Break when destination airport found
        std::pair<std::pair<airport, airport>, int> curr_edge = visited.front();
        visited.pop();
        airport dest_airport = curr_edge.first.second;

        int edge_status = bfs_adj[curr_edge.first.first.index][curr_edge.first.second.index].second;
        if (edge_status == 0) {
            if (airports_visited.at(dest_airport.index).second == true) 
                bfs_adj[curr_edge.first.first.index][curr_edge.first.second.index].second = 2;
            else {
                bfs_adj[curr_edge.first.first.index][curr_edge.first.second.index].second = 1;
                airports_visited.at(dest_airport.index).second = true;
                for (unsigned i = 0; i < dest_airport.connected.size(); i++) {
                    std::pair<airport, airport> route = std::make_pair(dest_airport,dest_airport.connected[i].first);
                    std::pair<std::pair<airport, airport>, int> edge = std::make_pair(route, 0);
                    visited.push(edge);
                }
            }
        }
    }

    // for (unsigned i = 0; i < bfs_adj.size(); i++) {
    // for (unsigned j = 0; j < bfs_adj[i].size(); j++) {
    //     std::cout << "   " << "Distance: " << bfs_adj[i][j].first << " " << "Status: " << bfs_adj[i][j].second << "   ";
    //     }
    // std::cout << " " << std::endl;
    // }



    if (visited.empty()) return -1;
    return backTrack(start, dest, bfs_adj);


}

double Graph::backTrack(airport start, airport dest, std::vector<std::vector<std::pair<double,int>>> bfs_adj) {
    double total_distance = 0.0;
    while (start.code != dest.code) {
        for (unsigned i = 0; i < bfs_adj.size(); i++) {
            if (bfs_adj[dest.index][i].second == 1) {
                total_distance += bfs_adj[dest.index][i].first;
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




//@TODO - AFTER BFS IMPLEMENTING
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
    // Checking for invalid aiport_name entries
    // khatija do not like
    // if (first_ap.code == ""|| second_ap.code == "") return -1.0; 

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
    
    // std::cout << "FIRST: " << line.at(2) << "   SECOND: " << line.at(3) << std::endl;

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