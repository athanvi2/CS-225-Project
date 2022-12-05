#include "graph.h"


int main() {
	Graph g("data_cleaning/airports_friends.csv", "data_cleaning/routes_friends.csv"); 
	std::cout << g.getDistance("KAT", "HAM") << std::endl;

	// for (auto e : g.airports.at(0).connected) {
	// 	std::cout << e.first.name << " Dist: " << e.second << std::endl;
	// }

	// for (auto cell : g.adj_[0]) {
	// 	std::cout << cell << " ";
	// }
	// std::cout << std::endl;

	// for (auto ap :g.airports) std::cout << ap.code << " ";
	// std::cout << std::endl;

	// std::cout << g.getDistance("DFW", "HDD") << std::endl;



	// std::cout << g.airports.at(3).latitude << std::endl;
	// std::cout << g.airports.at(3).longitude << std::endl;
	// std::cout << g.airports.at(3).code << std::endl;
	// std::cout << g.airports.at(3).code << std::endl;
	return 0;
}
