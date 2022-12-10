#include "graph.h"


int main() {
	Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 

	for (unsigned i = 0; i < g.pagerank_adj.size(); i++) {
		for (unsigned j = 0; j < g.pagerank_adj[i].size(); j++) {
			std::cout << g.pagerank_adj[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
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


	std::vector<std::vector<double>> test = g.adjWithDamping(g.connections, 0.85);
	
	std::cout << g.getLeastStopsDistance("KAT", "FIZ") << std::endl;
	std::cout << g.getShortestDistance("KAT", "FIZ") << std::endl;

	//JFK,EZE directly connected
	// Graph g2("../clean_airports.csv", "../clean_routes.csv");

	// std::vector<double> res2 = g2.PageRank(g2.pagerank_adj);
	// std::vector<double> norm2 = g2.NormalizedPageRank(res2);
	// for (unsigned i = 0; i < norm2.size(); i++) {
	// 	std::cout << norm2[i] << std::endl;
	// }
	// std::cout << "WE GUCCI!!!" << std::endl;

	// std::vector<std::string> top_airports2 = g2.PageRankResult(norm2, 10);
	// std::cout << "WE GUCCI!!!" << std::endl;
	// std::cout << "WE GUCCI!!!" << std::endl;
	// std::cout << "WE GUCCI!!!" << std::endl;


	// std::cout << g2.getLeastStopsDistance("JFK", "EZE") << std::endl;
	// std::cout << g2.getShortestDistance("JFK", "EZE") << std::endl;

	
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
