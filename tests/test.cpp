#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "graph.h"
#include "utils.h"
#include "airport.h"

/* Constructor tests */


/* Distance based on least number of stops between two airports tests (BFS Algorithm) */

// TEST_CASE("Distance based on least number of stops between two airports that do not connect #1 (SMALL GRAPH)", "[weight=1]") {
//     std::string airport_one = "ZAH";
//     std::string airport_two = "KAT";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getLeastStopsDistance(airport_one, airport_two);
//     REQUIRE(result == "-1");
// }

// TEST_CASE("Distance based on least number of stops between two airports that connect directly #1 (SMALL GRAPH)") {
//     std::string airport_one = "ZU";
//     std::string airport_two = "HAM";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getLeastStopsDistance(airport_one, airport_two);
//     REQUIRE(result == "14306");
   
// }

// TEST_CASE("Distance based on least number of stops between two airports that connect directly #2 (BIG GRAPH)") {
//     std::string airport_one = "JFK";
//     std::string airport_two = "EZE";
//     Graph g("../clean_airports.csv", "../clean_routes.csv");
//     std::string result = g.getLeastStopsDistance(airport_one, airport_two);
//     REQUIRE(result == "8534");
 
// }

// TEST_CASE("Distance based on least number of stops between two airports that connect indirectly #1 (SMALL GRAPH)") {
//     std::string airport_one = "KAT";
//     std::string airport_two = "FIZ";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getLeastStopsDistance(airport_one, airport_two);
//     REQUIRE(result == "16373");
  
// }

// TEST_CASE("Distance based on least number of stops between two airports that connect indirectly #2 (BIG GRAPH)") {
//     std::string airport_one = "AUS";
//     std::string airport_two = "LHR";
//     Graph g("../clean_airports.csv", "../clean_routes.csv");
//     std::string result = g.getLeastStopsDistance(airport_one, airport_two);
//     REQUIRE(result == "8066");
// }

// /* Distance based on shortest distance between two airports tests (Dijkstra's Algorithm) */

// TEST_CASE("Distance based on shortest distance between two airports that do not connect #1 (SMALL GRAPH)") {
//     std::string airport_one = "AMU";
//     std::string airport_two = "IDS";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getShortestDistance(airport_one, airport_two);
//     REQUIRE(result == "-1");
// }

// TEST_CASE("Distance based on shortest distance between two airports that connect directly #1 (SMALL GRAPH)") {
//     std::string airport_one = "ZU";
//     std::string airport_two = "HAM";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getShortestDistance(airport_one, airport_two);
//     REQUIRE(result == "14306");
   
// }

// TEST_CASE("Distance based on shortest distance between two airports that connect directly #2 (BIG GRAPH)") {
//     std::string airport_one = "JFK";
//     std::string airport_two = "EZE";
//     Graph g("../clean_airports.csv", "../clean_routes.csv");
//     std::string result = g.getShortestDistance(airport_one, airport_two);
//     REQUIRE(result == "8534");

// }

// TEST_CASE("Distance based on shortest distance between two airports that connect indirectly #1 (SMALL GRAPH)") {
//     std::string airport_one = "KAT";
//     std::string airport_two = "FIZ";
//     Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 
//     std::string result = g.getShortestDistance(airport_one, airport_two);
//     REQUIRE(result == "12499");

// }

// TEST_CASE("Distance based on shortest distance between two airports that connect indirectly #2 (BIG GRAPH)") {
//     std::string airport_one = "AUS";
//     std::string airport_two = "LHR";
//      Graph g("../clean_airports.csv", "../clean_routes.csv");
//     std::string result = g.getShortestDistance(airport_one, airport_two);
//     REQUIRE(result == "7907");
 
// }

TEST_CASE("PageRank - Size of adjacency matrix w/ damping (Small Dataset") {
    Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv");
    std::vector<std::vector<double>> adj_matrix_damp = g.adjWithDamping(g.connections, 0.85);
    
    int row_size = adj_matrix_damp.size();
    int col_size = adj_matrix_damp[0].size();

    std::string result = 
    "The row dimension is " + std::to_string(row_size) + ", and the column dimension is " + std::to_string(col_size);

    REQUIRE(result == "The row dimension is 10, and the column dimension is 10");
}

TEST_CASE("PageRank - Top 3 most popular 'airports' (Small Dataset") {
    Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv");
    std::vector<double> res = g.PageRank(g.pagerank_adj);
	std::vector<double> norm = g.NormalizedPageRank(res);
    std::vector<std::string> top_airports = g.PageRankResult(norm, 3);

    std::string result = "";
    for (unsigned i = 0; i < top_airports.size(); i++) {
        result += top_airports[i] + ", ";
    }
    result.pop_back();
    result.pop_back();
    REQUIRE(result == "IDS, IBS, KAT");
}

TEST_CASE("PageRank - Least popular 'airport' (Small Dataset") {
    Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv");
    std::vector<double> res = g.PageRank(g.pagerank_adj);
	std::vector<double> norm = g.NormalizedPageRank(res);
    std::vector<std::string> top_airports = g.PageRankResult(norm, norm.size());

    std::string result = top_airports[top_airports.size() - 1];
    REQUIRE(result == "MAZ");
}

TEST_CASE("PageRank - Top 5 most popular airports (Big Dataset") {
    Graph g2("../clean_airports.csv", "../clean_routes.csv");
    std::vector<double> res = g2.PageRank(g2.pagerank_adj);
	std::vector<double> norm = g2.NormalizedPageRank(res);
    std::vector<std::string> top_airports = g2.PageRankResult(norm, 5);

    std::string result = "";
    for (unsigned i = 0; i < top_airports.size(); i++) {
        result += top_airports[i] + ", ";
    }
    result.pop_back();
    result.pop_back();
    REQUIRE(result == "ATL, ORD, DEN, PEK, LAX");
}
