#include "graph.h"


int main() {
	Graph g("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv"); 

	// for (auto e : g.airports.at(0).connected) {
	// 	std::cout << e.first.name << " Dist: " << e.second << std::endl;
	// }

	// for (auto cell : g.adj_[0]) {
	// 	std::cout << cell << " ";
	// }
	// std::cout << std::endl;

	// for (auto ap :g.airports) std::cout << ap.code << " ";
	// std::cout << std::endl;

	std::cout << g.getDistance("DFW", "HDD") << std::endl;



	// std::cout << g.airports.at(3).latitude << std::endl;
	// std::cout << g.airports.at(3).longitude << std::endl;
	return 0;
}
