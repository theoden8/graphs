#include "Graph.hpp"
#include "Debug.hpp"

#include <cassert>
#include <cmath>

#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <deque>

// will ignore distances
std::vector <Edge::dist_t> Graph::bfs(const label_t from) const {
	ASSERT_DOMAIN(from < Size());

	std::queue <label_t> spiral;
	std::vector <Edge::dist_t> distances(Size(), Edge::DIST_UNDEF);

	distances[from] = 0;
	spiral.push(from);

	while(!spiral.empty()) {
		const Node &nd = nodes_[spiral.front()];
		spiral.pop();
		for(const auto &it : nd.get_ports()) {
			const label_t id = it.first;
			if(distances[id] == Edge::DIST_UNDEF && (nd >> id)) {
				distances[id] = distances[nd.id()] + 1;
				spiral.push(id);
			}
		}
	}
	return distances;
}

// will ignore distances
Edge::dist_t Graph::bfs_bidirectional(const label_t from1, const label_t from2) const {
	ASSERT_DOMAIN(from1 < Size() && from2 < Size());
	if(from1 == from2)
		return Edge::dist_t(0);
	using queue_t = std::queue<label_t>;
	using dists_t = std::vector<Edge::dist_t>;
	std::pair <queue_t, dists_t> bfs[2] = {
		std::make_pair(queue_t(), dists_t(Size(), Edge::DIST_UNDEF)),
		std::make_pair(queue_t(), dists_t(Size(), Edge::DIST_UNDEF)),
	};
	std::vector <bool> common_map(Size(), false);
	bfs[0].second[from1] = bfs[1].second[from2] = 0;
	common_map[from1] = common_map[from2] = true;
	bfs[0].first.push(from1), bfs[1].first.push(from2);
	while(!bfs[0].first.empty() && !bfs[1].first.empty()) {
		for(label_t i = 0; i < 2; ++i) {
			const Node &nd = GetNodes()[bfs[i].first.front()];
			bfs[i].first.pop();
			for(const auto &it : nd.get_ports()) {
				const label_t id = it.first;
				if(bfs[i].second[id] == Edge::DIST_UNDEF && (nd >> id)) {
					bfs[i].second[id] = bfs[i].second[nd.id()] + 1;
					if(common_map[id] == true) {
						return bfs[0].second[id] + bfs[1].second[id];
					}
					bfs[i].first.push(id);
					common_map[id] = true;
				}
			}
		}
	}
	return Edge::DIST_UNDEF;
}

std::vector <bool> Graph::dfs(const label_t from) const {
	ASSERT_DOMAIN(from < Size());
	std::stack <label_t> depth;
	std::vector <bool> discovered(Size(), false);
	depth.push(from);
	while(!depth.empty()) {
		const Node &nd = GetNodes()[depth.top()];
		depth.pop();

		if(discovered[nd.id()] == false) {
			discovered[nd.id()] = true;
			for(const auto &it : nd.get_ports())
				if(nd >> it.first)
					depth.push(it.first);
		}
	}
	return discovered;
}

std::vector <Edge::dist_t> Graph::dijkstra(const label_t from) const {
	using priority_t = std::pair <Edge::dist_t, label_t>;
	ASSERT_DOMAIN(from < Size());
	std::vector <Edge::dist_t> distances(Size(), Edge::DIST_MAX);
	std::priority_queue <priority_t> pqueue;
	distances[from] = 0;
	pqueue.push(std::make_pair(0, from));
	while(!pqueue.empty()) {
		const Node &nd = GetNodes()[pqueue.top().second];
		pqueue.pop();
		for(const auto &it : nd.get_ports()) {
			const label_t outbound = it.first;
			if(nd >> outbound) {
				ASSERT_DOMAIN(it.second.dist >= 0);
				const Edge::dist_t new_dist = it.second.dist + distances[nd.id()];
				if(distances[outbound] > new_dist) {
					distances[outbound] = new_dist;
					pqueue.push(std::make_pair(new_dist, nd.id()));
				}
			}
		}
	}
	return distances;
}
