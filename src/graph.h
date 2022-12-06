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

        /**
         * @brief The BFS queue takes edges, but ensures no cycles or repeated edges by 
         *        marking nodes as visited or not. Each edge is marked as either 0 or 1
         *        with direction mattering. This way we can properly backtrack by following
         *        which nodes we came from
         * 
         * @param start Starting airport
         * @param dest Airport we want to reach to
         * @returns shortest path in *steps* to the dest
        */
        double BFS(airport start, airport dest);

        /**
         * @brief 
         * 
         * @param start Starting airport
         * @param dest Airport we want to reach to
         * @returns shortest path in *distance* to the dest
        */
       double Dijkstra(airport start, airport dest);


        /**
         * @param start Starting airport
         * @param dest Airport we want to reach to
         * @param bfs_adj adj matrix that additionally stores the status of each edge
         * 
         * @returns the total distance by backtracking from dest to start
        */
        double backTrack(airport start, airport dest, std::vector<std::vector<std::pair<double,int>>> bfs_adj);

    private:
        /* Vector of all vertices */ 
        std::vector<airport> airports;
        /* Vector of all edges */
        std::vector<std::pair<airport, airport>> routes;
        /* 
         * Adjacency matrix: Every airport has an index data member based on its position
         * in the airports vector. To access a distance between two airports given a string,
         * get the airport by comparing the code given to existing airports, then search
         * adj_[airport_one.index][airport_two.index]
         */
        std::vector<std::vector<double>> adj_;

         /**
          * @note change to an aiport in airports vector does not make the airport in routes vector change or vice versa
          *       To resolve this, whenever accessing an airport, access it by getting the airport directly from the 
          *       airports vector
          */
        
        
};