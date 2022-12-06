#include "graph.h"


int main() {
	Graph g("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicates.csv"); 
	// std::cout << g.getDistance("KAT", "FIZ") << std::endl;
	std::cout << g.Dijkstra(g.convertCodeToAirport("KAT"), g.convertCodeToAirport("ZU")) << std::endl;

	// Graph g2("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");
	// std::cout << g2.getDistance("AUS", "LHR") << std::endl;

	
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
