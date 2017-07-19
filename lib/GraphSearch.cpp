#include "Graph.hpp"
#include "Debug.hpp"

#include <cassert>
#include <cmath>

#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <utility>

// will ignore distances
Graph::list_t <Edge::dist_t> Graph::bfs(const label_t from) const {
	ASSERT_DOMAIN(from < Size());

	std::queue <label_t> spiral;
	list_t <Edge::dist_t> distances(Size(), Edge::DIST_UNDEF);

	distances[from] = 0;
	spiral.push(from);

	while(!spiral.empty()) {
		const Node &nd = nodes_[spiral.front()];
		spiral.pop();
		for(const auto &[out_id, edge] : nd.get_ports()) {
			if(distances[out_id] == Edge::DIST_UNDEF && edge.is_out()) {
				distances[out_id] = distances[nd.id()] + 1;
				spiral.push(out_id);
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
	struct { queue_t &&lqueue; dists_t &&dists; } bfs[2] = {
		{
			queue_t(),
			dists_t(Size(), Edge::DIST_UNDEF)
		}, {
			queue_t(),
			dists_t(Size(), Edge::DIST_UNDEF)
		},
	};
	list_t <bool> common_map(Size(), false);
	bfs[0].dists[from1] = bfs[1].dists[from2] = 0;
	common_map[from1] = common_map[from2] = true;
	bfs[0].lqueue.push(from1), bfs[1].lqueue.push(from2);
	while(!bfs[0].lqueue.empty() && !bfs[1].lqueue.empty()) {
		for(label_t i = 0; i < 2; ++i) {
			const Node &nd = GetNodes()[bfs[i].lqueue.front()];
			bfs[i].lqueue.pop();
			for(const auto &[out_id, edge] : nd.get_ports()) {
				if(bfs[i].dists[out_id] == Edge::DIST_UNDEF && edge.is_out()) {
					bfs[i].dists[out_id] = bfs[i].dists[nd.id()] + 1;
					if(common_map[out_id] == true)
						return bfs[0].dists[out_id] + bfs[1].dists[out_id];
					bfs[i].lqueue.push(out_id);
					common_map[out_id] = true;
				}
			}
		}
	}
	return Edge::DIST_UNDEF;
}

Graph::list_t <bool> Graph::dfs(const label_t from) const {
	ASSERT_DOMAIN(from < Size());
	std::stack <label_t> depth;
	list_t <bool> discovered(Size(), false);
	depth.push(from);
	while(!depth.empty()) {
		const Node &nd = GetNodes()[depth.top()];
		depth.pop();
		if(discovered[nd.id()] == false) {
			discovered[nd.id()] = true;
			for(const auto &[out_id, edge] : nd.get_ports())
				if(edge.is_out())
					depth.push(out_id);
		}
	}
	return discovered;
}

Graph::list_t <Edge::dist_t> Graph::dijkstra(const label_t from) const {
	ASSERT_DOMAIN(from < Size());
	list_t <Edge::dist_t> d(Size(), Edge::DIST_UNDEF);
	std::priority_queue <std::pair<Edge::dist_t, label_t> > pq;
	d[from] = 0;
	pq.push(std::make_pair(0, from));
	while(!pq.empty()) {
		const Node &nd = GetNodes()[pq.top().second];
		const size_t u = nd.id();
		pq.pop();
		for(const auto &[v, e] : nd.get_ports()) {
			if(e.is_out()) {
				ASSERT_DOMAIN(e.dist != Edge::DIST_UNDEF);
				ASSERT_DOMAIN(e.dist >= 0);
				const Edge::dist_t new_dist = d[u] + e.dist;
				if(d[v] == Edge::DIST_UNDEF || new_dist < d[v]) {
					d[v] = new_dist;
					pq.push({new_dist, v});
				}
			}
		}
	}
	return d;
}

Graph::list_t <Edge::dist_t> Graph::bellman_ford(const label_t from) const {
	list_t <Edge::dist_t> d(Size(), Edge::DIST_UNDEF);
	d[from] = 0;
	/* puts("START OF BELLMAN_FORD"); */
	/* Print(); */
	for(size_t i = 0; i < GetNodes().size() + 1; ++i)
		for(const auto &nd : GetNodes()) {
			const size_t u = nd.id();
			for(const auto &[v, e] : nd.get_ports()) {
				if(e.is_out() && (
						(d[v] == Edge::DIST_UNDEF || d[v] > d[u] + e.dist) && d[u] != Edge::DIST_UNDEF))
				{
					ASSERT_DOMAIN(e.dist != Edge::DIST_UNDEF);
					if(i == GetNodes().size())
						throw std::runtime_error("error: something's not right");
					d[v] = d[u] + e.dist;
				}
			}
		}
	/* for(auto&it:d)std::cout<<it<<" ";std::cout<<std::endl; */
	/* for(auto&it:d)ASSERT_DOMAIN(it == Edge::DIST_UNDEF || it >= 0); */
	/* puts("END OF BELLMAN_FORD"); */
	return d;
}

Graph::list_t <Edge::dist_t> Graph::levit(const label_t from) const {
	list_t <Edge::dist_t> d(Size(), Edge::DIST_MAX);
	d[from] = 0;
	// TODO
	return d;
}

Graph::mat_t <Edge::dist_t> Graph::floyd() const {
	mat_t <Edge::dist_t> matr(Size(), list_t <Edge::dist_t> (Size(), Edge::DIST_UNDEF));
	for(auto &nd : GetNodes())
		for(const auto &[out_id, edge] : nd.get_ports())
			if(edge.is_out())
				matr[nd.id()][out_id] = edge.dist;
	// TODO
	return matr;
}

// needs working dijkstra and bellman-ford
Graph::mat_t <Edge::dist_t> Graph::johnsson() const {
	mat_t <Edge::dist_t> matr(Size(), list_t <Edge::dist_t> (Size(), Edge::DIST_UNDEF));
	// TODO
	return matr;
}
