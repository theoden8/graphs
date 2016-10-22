#include <cassert>
#include <cmath>

#include <functional>
#include <queue>
#include <stack>
#include <vector>

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


// raw implementation
std::vector <Edge::dist_t> Graph::dijkstra(const size_t from) const {
	std::vector <Edge::dist_t> distances(Size(), Edge::DIST_MAX);
	std::priority_queue <size_t, std::vector <size_t>, std::greater <size_t> > pqueue;
	std::vector <bool>
		is_active(Size(), true),
		in_pqueue(Size(), false);

	distances[from] = 0;
	while(!pqueue.empty()) {
		const Node &nd = nodes_[pqueue.top()];
		pqueue.pop();

		if(!is_active[nd.id()])
			continue;

		for(const auto &it : nd.get_ports()) {
			const size_t dest = it.first;
			const Edge::dist_t dist = it.second.dist;
			assert(dist > 0);

			distances[dest] = std::min(distances[dest], distances[nd.id()] + dist);

			if(is_active[dest] && !in_pqueue[dest]) {
				in_pqueue[dest] = true;
				// should use pair <distance, vert>
				pqueue.push(dest);
			}
		}

		is_active[nd.id()] = false;
	}

	return distances;
}
