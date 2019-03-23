#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

#include "Node.hpp"

#define INT2MASK(INT) (1 << ((INT) - 1))

class Graph {
protected:
	using label_t = size_t;
	template <typename A> using list_t = std::vector<A>;
	template <typename A> using mat_t = list_t <list_t <A> >;
	using nodes_t = list_t<Node>;
	const Edge::mask_t properties_;
	nodes_t nodes_;
public:
	typedef enum {
		SIMPLEGRAPH,
		PSEUDOGRAPH,
		DIRECTEDGRAPH,
	} PROPERTY;

	Graph();
	Graph(Edge::mask_t properties);
	Graph(size_t size, Edge::mask_t properties);
	~Graph();

	Edge::mask_t GetProperties() const;
	bool Is(Edge::mask_t property) const;
	void Print() const;

// GraphEdges
	const nodes_t &GetNodes() const;
	size_t Size() const;
	Node &operator[] (label_t idx);
	Node operator[] (label_t idx) const;
	void AddNode();
	void Connect(
		label_t id1,
		label_t id2,
		Edge::dist_t dist = Edge::DIST_DEFAULT,
		Edge::bandwidth_t bwidth = Edge::BWIDTH_DEFAULT
	);
	void RandomlyConnect();
	static Graph Random(size_t size);
// GraphSearch
	list_t <Edge::dist_t> bfs(const label_t from) const;
	Edge::dist_t bfs_bidirectional(const label_t from1, const label_t from2) const;
	/* Edge::dist_t a_star_search(const label_t from1, const label_t from2) const; */
	list_t <bool> dfs(const label_t from) const;
	list_t <Edge::dist_t> dijkstra(const label_t from) const;
	list_t <Edge::dist_t> bellman_ford(const label_t from) const;
	list_t <Edge::dist_t> levit(const label_t from) const;
	mat_t <Edge::dist_t> floyd() const;
	mat_t <Edge::dist_t> johnsson() const;
// GraphColoring
// GraphAttributes
public:
	typedef bool(graph_checker()const);
	graph_checker
		IsSimpleGraph, IsPseudoGraph, IsDirectedGraph,
		IsWeaklyConnected, IsStronglyConnected, IsConnected,
		IsAcyclic, IsDAG, IsTree, IsBipartite;
// GraphMatrices
	mat_t <bool> adj_matrix() const;
	static Graph from_adj_matrix(mat_t <bool> &adj);
	mat_t <bool> incidence_matrix() const;
	static Graph from_incidence_matrix(mat_t <bool> &inc);
	mat_t <Edge::dist_t> dist_matrix() const;
	static Graph from_dist_matrix(mat_t <Edge::dist_t> &dist);
// GraphDAG
	typedef Graph DAG;
	list_t <label_t> topological_sort();
// GraphTree
	typedef Graph Tree;
	size_t diameter() const;
	list_t <label_t> prufer_encode() const;
	static Tree prufer_decode(list_t <Edge::dist_t> prufer);
// GraphSpanningTree
};
