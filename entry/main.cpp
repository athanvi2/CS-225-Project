#include "graph.h"


int main() {

	std::cout << "Connections vector for smaller csv:" << std::endl;
	std::cout << std::endl;
	Graph g("../airports_friends.csv", "../route_friends_wo_duplicates.csv"); 

    for (unsigned i = 0; i < g.connections.size(); i++) {
        for (unsigned j = 0; j < g.connections[i].size(); j++) {
           std::cout << g.connections[i][j] << " ";
        }
		std::cout << std::endl;
    }


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Least stops:" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << g.getLeastStopsDistance("KAT", "FIZ") << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Shortest Distance:" << std::endl;
	std::cout << g.getShortestDistance("KAT", "FIZ") << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Pagerank adj vector for smaller csv:" << std::endl;
	std::cout << std::endl;
    for (unsigned i = 0; i < g.pagerank_adj.size(); i++) {
        for (unsigned j = 0; j < g.pagerank_adj[i].size(); j++) {
           std::cout << g.pagerank_adj[i][j] << " ";
        }
		std::cout << std::endl;
    }

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "Most popular airports- top 10 for bigger csv" << std::endl;
	std::cout << std::endl;
	Graph g2("../clean_airports.csv", "../clean_routes.csv");\
	std::vector<double> res2 = g2.PageRank(g2.pagerank_adj);
	std::vector<double> norm2 = g2.NormalizedPageRank(res2);
	std::vector<std::string> top_airports2 = g2.PageRankResult(norm2, 10);

	for (auto i : top_airports2) {
		std::cout << i << std::endl;
	}
}
