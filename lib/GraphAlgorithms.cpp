#include <cassert>
#include <iostream>

#include <queue>
#include <stack>
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
				distances[id] = distances[nd.id()] + 1;
				spiral.push(id);
			}
		}
	}
	return distances;
}


std::vector <bool> Graph::dfs(const size_t from) const {
	assert(from < Size());

	std::stack <size_t> stck;
	std::vector <bool> labels(Size(), false);

	stck.push(from);
	while(!stck.empty()) {
		const Node &nd = nodes_[stck.top()];
		stck.pop();

		if(labels[nd.id()] == false) {
			labels[nd.id()] = true;
			for(const auto &it : nd.get_ports())
				if(nd >> it.first)
					stck.push(it.first);
		}
	}

	return labels;
}
