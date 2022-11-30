#include "utils.h"
#include "airport.h"

class Graph {
    public:
        Graph(std::string aiport_csv, std::string routes_csv);
        int getDistance(std::string airport_one, std::string airport_two);
        


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
    private:
        /* Index of aiport vertex is its index in adj */ 
        std::vector<airport> airports; 
        /* Vector of all edges */
        std::vector<std::pair<airport, airport>> routes;
        /* Adjacency matrix */
        std::vector<std::vector<int>> adj_;
};


/*
1) Shortest distance between two airports
2) a) If directly connected, compute distance
   b) BFS

*/