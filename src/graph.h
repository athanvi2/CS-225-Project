#pragma once
#include "utils.h"
#include "airport.h"

class Graph {
    public:

        /**
         * @param airport_csv file containing aiports
         * @param routes_csv file containing routes between airports
         * Populates vertices and edges matrix and adj matrix
        */
        Graph(std::string aiport_csv, std::string routes_csv);

        /**
         * @param airport_one code for airport
         * @param airport_two code for airport
         * @returns distance, even if indirect will use BFS to determine shortest path
        */
        double getDistance(std::string airport_one, std::string airport_two);

        /**
         * @param airport_one
         * @param aiport_two both must be codes and directly connected for this function to work
         * @returns distance between two airports, only works with airports that are directly connected
        */
        double calcEdgeDistance(std::string airport_one, std::string airport_two);
        
        /**
         * @param curr_airport airport to get all the connected airports for
         * @returns vector of pairs, each pair has the airport struct that it is connected to and then double as
         *          the distance between the two
        */
        std::vector<std::pair<airport,double>> getConnected(airport curr_airport);

        /**
         * @param line a line of info about an airport
         * @returns Takes one line of airports and creates an airport struct 
         */
        airport createAirport(std::vector<std::string> line); 

        /**
         * @param ap airport to add to vertex vector
        */
        void insertVertex(airport ap);

        /** 
         * @param line one route, (Airport start, Airport end) to add to edge list
         */
        void insertEdge(std::vector<std::string> line);

        /**
         * @param airport_code airport code that we want to get the airport struct obj of
         * @returns the airport struct
        */
        airport convertCodeToAirport(std::string airport_code);

        std::vector<airport> airports;

    private:
        /* Vector of all vertices */ 
         
        /* Vector of all edges */
        std::vector<std::pair<airport, airport>> routes;
        /* 
         * Adjacency matrix: Every airport has an index data member based on its position
         * in the airports vector. To access a distance between two airports given a string,
         * get the airport by comparing the code given to existing airports, then search
         * adj_[airport_one.index][airport_two.index]
         */
        std::vector<std::vector<double>> adj_;
};


/*
1) Shortest distance between two airports
2) a) If directly connected, compute distance
   b) BFS

*/