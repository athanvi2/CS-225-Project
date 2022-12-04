#include "graph.h"


int main() {
	Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes_short.csv"); 
	// std::cout << g.airports.at(3).latitude << std::endl;
	// std::cout << g.airports.at(3).longitude << std::endl;
	return 0;
}
