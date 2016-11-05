#include <cassert>
#include <cmath>

#include <functional>
#include <vector>
#include <stack>
#include <queue>

#include "Graph.hpp"

// will ignore distances
std::vector <Edge::dist_t> Graph::bfs(const size_t from) const {
	assert(from < Size());

	std::queue <size_t> spiral;
	std::vector <Edge::dist_t> distances(Size(), Edge::DIST_UNDEF);

	distances[from] = 0;
	spiral.push(from);

	while(!spiral.empty()) {
		const Node &nd = nodes_[spiral.front()];
		spiral.pop();

		for(const auto &it : nd.get_ports()) {
			const size_t id = it.first;
			if(distances[id] == Edge::DIST_UNDEF && (nd >> id)) {
				distances[id] = distances[nd.id()] + 1;
				spiral.push(id);
			}
		}
	}
	return distances;
}


std::vector <bool> Graph::dfs(const size_t from) const {
	assert(from < Size());

	std::stack <size_t> depth;
	std::vector <bool> labels(Size(), false);

	depth.push(from);
	while(!depth.empty()) {
		const Node &nd = nodes_[depth.top()];
		depth.pop();

		if(labels[nd.id()] == false) {
			labels[nd.id()] = true;
			for(const auto &it : nd.get_ports())
				if(nd >> it.first)
					depth.push(it.first);
		}
	}

	return labels;
}


typedef std::pair <Edge::dist_t, size_t> priority_t;
std::vector <Edge::dist_t> Graph::dijkstra(const size_t from) const {
	std::vector <Edge::dist_t> distances(Size(), Edge::DIST_MAX);
	std::priority_queue <priority_t> pqueue;
	distances[from] = 0;
	pqueue.push(std::make_pair(0, from));
	while(!pqueue.empty()) {
		const Node &nd = nodes_[pqueue.top().second];
		pqueue.pop();

		for(const auto &it : nd.get_ports()) {
			const size_t outbound = it.first;
			assert(it.second.dist >= 0);
			const Edge::dist_t new_dist = it.second.dist + distances[nd.id()];
			if(distances[outbound] > new_dist) {
				distances[outbound] = new_dist;
				pqueue.push(std::make_pair(new_dist, nd.id()));
			}
		}
	}

	return distances;
}
