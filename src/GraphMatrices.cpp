#include "Graph.hpp"
#include "Debug.hpp"

Graph::mat_t <bool> Graph::adj_matrix() const {
	mat_t <bool> adj(Size(), list_t<bool>(Size(), 0));
	for(size_t i = 0; i < Size(); ++i)
		for(size_t j = 0; j < Size(); ++j)
			adj[i][j] = ((*this)[i] >> (*this)[j]) ? true : false;
	return adj;
}

Graph Graph::from_adj_matrix(mat_t <bool> &adj) {
	for(size_t i = 0; i < adj.size(); ++i) {
		ASSERT_DOMAIN(adj[i].size() == adj.size());
	}
	Graph G(adj.size(), DIRECTEDGRAPH | PSEUDOGRAPH);
	for(size_t i = 0; i < G.Size(); ++i)
		for(size_t j = 0; j < G.Size(); ++j)
			if(adj[i][j])
				G.Connect(i, j);
	return G;
}

Graph::mat_t <bool> Graph::incidence_matrix() const {
	mat_t <bool> inc(Size(), list_t <bool>(Size(), false));
	for(size_t i = 0; i < Size(); ++i)
		for(size_t j = 0; j < Size(); ++j)
			; // TODO
	return inc;
}

Graph::mat_t <Edge::dist_t> Graph::dist_matrix() const {
	mat_t <Edge::dist_t> d(Size(), list_t<Edge::dist_t>(Size(), Edge::DIST_UNDEF));
	for(const auto &n : GetNodes()) {
		d[n.id()][n.id()] = 0;
		for(auto &[id, e] : n.get_ports()) {
			if(e.is_out()) {
				d[n.id()][id] = e.dist;
			}
		}
	}
	return d;
}

Graph Graph::from_dist_matrix(mat_t <Edge::dist_t> &dist) {
	for(size_t i = 0; i < dist.size(); ++i)
		ASSERT_DOMAIN(dist.size() == dist[i].size());
	Graph G(dist.size(), PSEUDOGRAPH | DIRECTEDGRAPH);
	for(size_t i = 0; i < G.Size(); ++i)
		for(size_t j = 0; j < G.Size(); ++j)
			if(dist[i][j] != Edge::DIST_UNDEF)
				G.Connect(i, j, dist[i][j]);
	return G;
}
