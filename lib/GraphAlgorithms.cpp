#include <cassert>
#include <iostream>

#include <queue>
#include <vector>

#include "Graph.hpp"

const Graph::dist_t Graph::UNDEFINED = -1;

std::vector <Graph::dist_t> Graph::bfs(const size_t from) const {
	assert(from < Size());

	std::queue <size_t> spiral;
	std::vector <dist_t> distances(Size(), UNDEFINED);

	distances[from] = 0;
	spiral.push(from);

	while(!spiral.empty()) {
		const Node &nd = nodes_[spiral.front()];
		spiral.pop();

		for(const auto &it : nd.get_ports()) {
			const size_t id = it.first;
			if(distances[id] == UNDEFINED && (nd >> id)) {
				if(id == 98)
					std::cout << nd.id() << std::endl;
				distances[id] = distances[nd.id()] + 1;
				spiral.push(id);
			}
		}
	}
	return distances;
}
