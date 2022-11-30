#pragma once
#include "utils.h"
#include "airport.h"

class Graph {
    public:
        Graph(std::string aiport_csv, std::string routes_csv);
        /**
         * @param airport_one code for airport
         * @param airport_two code for airport
        */
        double getDistance(std::string airport_one, std::string airport_two);

        /**
         * @param airport_one
         * @param aiport_two both must be codes and directly connected for this function to work
        */
        double calcEdgeDistance(std::string airport_one, std::string airport_two);
        


        /* getter for all connected airports */
        std::map<airport, double> getConnected(airport curr_airport);
        /**
         * @param line a line of info about an airport
         * Takes one line of airports and creates an airport struct 
         */
        airport createAirport(std::vector<std::string> line); 

        /* Puts an aiport into the graph */
        void insertVertex(airport Airport);

        /** Puts the edge into the graph, @
         * @param line one route, (Airport start, Airport end)
         */
        void insertEdge(std::vector<std::string> line);

        /**
         * @param airport_code airport code that we want to get the airport struct obj of
        */
        airport convertCodeToAirport(std::string airport_code);
    private:
        /* Vector of all vertices */ 
        std::vector<airport> airports; 
        /* Vector of all edges */
        std::vector<std::pair<airport, airport>> routes;
        /* Adjacency matrix: key is start airport, value is map with (K,V) as (dest airport, distance) */
        std::map<airport, std::map<airport, double>> adj_;
};


/*
1) Shortest distance between two airports
2) a) If directly connected, compute distance
   b) BFS

*/