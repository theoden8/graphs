#include <cassert>
#include <iostream>

#include <queue>
#include <vector>

#include "Graph.hpp"

const int Graph::UNDEFINED = -1;

std::vector <int> Graph::bfs(const size_t from) const {
	assert(from < Size());
	std::queue <size_t> spiral;
	std::vector <int> distances(Size(), UNDEFINED);
	distances[from] = 0;
	while(!spiral.empty()) {
		const Node &nd = nodes_[spiral.front()];
		spiral.pop();
		for(const auto &it : nd.get_ports()) {
			const size_t id = it.first;
			if(!(nd >> id) || distances[id] == UNDEFINED)
				continue;
			distances[id] = distances[nd.id()] + 1;
			spiral.push(id);
		}
	}
	return distances;
}
