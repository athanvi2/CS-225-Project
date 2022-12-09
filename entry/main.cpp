#include "graph.h"


int main() {
	Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 

	std::vector<double> res = g.PageRank(g.pagerank_adj);
	std::vector<double> norm = g.NormalizedPageRank(res);
	for (unsigned i = 0; i < norm.size(); i++) {
		std::cout << norm[i] << std::endl;
	}
	std::cout << "WE GUCCI!!!" << std::endl;

	std::vector<std::string> top_airports = g.PageRankResult(norm, 10);
	std::cout << "WE GUCCI!!!" << std::endl;
	std::cout << "WE GUCCI!!!" << std::endl;
	std::cout << "WE GUCCI!!!" << std::endl;
	for (auto i : top_airports) {
		std::cout << i << std::endl;
	}


	// // std::vector<std::vector<double>> test = g.adjWithDamping(g.connections, 0.85);
	// for (auto i : rank) {
	// 		std::cout << i << std::endl;
	// }

	// std::cout << g.getLeastStopsDistance("KAT", "FIZ") << std::endl;
	// std::cout << g.getShortestDistance("KAT", "FIZ") << std::endl;

	// JFK,EZE directly connected
	//Graph g2("data_cleaning/clean_airports.csv", "data_cleaning/clean_routes.csv");

	// std::vector<double> res = g2.PageRank(g2.pagerank_adj);
	// std::vector<double> norm = g2.NormalizedPageRank(res);
	// for (unsigned i = 0; i < norm.size(); i++) {
	// 	std::cout << norm[i] << std::endl;
	// }
	// std::cout << "WE GUCCI!!!" << std::endl;

	// std::vector<std::string> top_airports = g2.PageRankResult(norm, 10);
	// std::cout << "WE GUCCI!!!" << std::endl;
	// std::cout << "WE GUCCI!!!" << std::endl;
	// std::cout << "WE GUCCI!!!" << std::endl;
	// for (auto i : top_airports) {
	// 	std::cout << i << std::endl;
	// }


	//std::cout << g2.getLeastStopsDistance("JFK", "EZE") << std::endl;
	//std::cout << g2.getShortestDistance("JFK", "EZE") << std::endl;

	
	// for (auto e : g.airports.at(0).connected) {
	// 	std::cout << e.first.name << " Dist: " << e.second << std::endl;
	// }
	
	//Graph g3("data_cleaning/airports_friends.csv", "data_cleaning/route_friends_wo_duplicate.csv");
	// for (auto row : g3.getAdj()) {
	// 	for (auto cell : row) {
	// 		std::cout << cell << " ";
	// 	}
	// }
	// std::cout << std::endl;

	// for (auto ap :g.airports) std::cout << ap.code << " ";
	// std::cout << std::endl;

	// std::cout << g.getDistance("DFW", "HDD") << std::endl;



	// std::cout << g.airports.at(3).latitude << std::endl;
	// std::cout << g.airports.at(3).longitude << std::endl;
	// std::cout << g.airports.at(3).code << std::endl;
	// std::cout << g.airports.at(3).code << std::endl;
}
