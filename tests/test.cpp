#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../graph.h"
#include "../utils.h"
#include "../airport.h"

/* Constructor tests */


/* Distance based on least number of stops between two airports tests (BFS Algorithm) */

TEST_CASE("Distance based on least number of stops between two airports that do not connect #1 (SMALL GRAPH)") {
    std::string airport_one = "ZAH";
    std::string airport_two = "KAT";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getLeastStopsDistance(airport_one, airport_two);
    REQUIRE(int(result) == -1);
}

TEST_CASE("Distance based on least number of stops between two airports that connect directly #1 (SMALL GRAPH)") {
    std::string airport_one = "ZU";
    std::string airport_two = "HAM";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getLeastStopsDistance(airport_one, airport_two);
    REQUIRE(int(result) == 14306);
   
}

TEST_CASE("Distance based on least number of stops between two airports that connect directly #2 (BIG GRAPH)") {
    std::string airport_one = "JFK";
    std::string airport_two = "EZE";
    Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");
    double result = g.getLeastStopsDistance(airport_one, airport_two);
    REQUIRE(int(result) == 8534);
 
}

TEST_CASE("Distance based on least number of stops between two airports that connect indirectly #1 (SMALL GRAPH)") {
    std::string airport_one = "KAT";
    std::string airport_two = "FIZ";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getLeastStopsDistance(airport_one, airport_two);
    REQUIRE(int(result) == 16373);
  
}

TEST_CASE("Distance based on least number of stops between two airports that connect indirectly #2 (BIG GRAPH)") {
    std::string airport_one = "AUS";
    std::string airport_two = "LHR";
    Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");
    double result = g.getLeastStopsDistance(airport_one, airport_two);
    REQUIRE(int(result) == 8066);
}

/* Distance based on shortest distance between two airports tests (Dijkstra's Algorithm) */

TEST_CASE("Distance based on shortest distance between two airports that do not connect #1 (SMALL GRAPH)") {
    std::string airport_one = "AMU";
    std::string airport_two = "IDS";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getShortestDistance(airport_one, airport_two);
    REQUIRE(int(result) == -1);
}

TEST_CASE("Distance based on shortest distance between two airports that connect directly #1 (SMALL GRAPH)") {
    std::string airport_one = "ZU";
    std::string airport_two = "HAM";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getShortestDistance(airport_one, airport_two);
    REQUIRE(int(result) == 14306);
   
}

TEST_CASE("Distance based on shortest distance between two airports that connect directly #2 (BIG GRAPH)") {
    std::string airport_one = "JFK";
    std::string airport_two = "EZE";
    Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");
    double result = g.getShortestDistance(airport_one, airport_two);
    REQUIRE(int(result) == 8534);

}

TEST_CASE("Distance based on shortest distance between two airports that connect indirectly #1 (SMALL GRAPH)") {
    std::string airport_one = "KAT";
    std::string airport_two = "FIZ";
    Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
    double result = g.getShortestDistance(airport_one, airport_two);
    REQUIRE(int(result) == 12499);

}

TEST_CASE("Distance based on shortest distance between two airports that connect indirectly #2 (BIG GRAPH)") {
    std::string airport_one = "AUS";
    std::string airport_two = "LHR";
     Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");
    double result = g.getShortestDistance(airport_one, airport_two);
    REQUIRE(int(result) == 7907);
 
}