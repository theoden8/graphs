#pragma once

#include <vector>
#include <unordered_map>
#include <functional>

#include "Node.hpp"

#define INT2MASK(INT) (1 << ((INT) - 1))

class Graph {
protected:
	using label_t = size_t;
	using nodes_t = std::vector<Node>;
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
	void Connect(label_t id1, label_t id2, Edge::dist_t dist = Edge::DIST_DEFAULT);
// GraphSearch
	std::vector<Edge::dist_t> bfs(const label_t from) const;
	Edge::dist_t bfs_bidirectional(const label_t from1, const label_t from2) const;
	/* Edge::dist_t a_star_search(const label_t from1, const label_t from2) const; */
	std::vector <bool> dfs(const label_t from) const;
	std::vector <Edge::dist_t> dijkstra(const label_t from) const;
// GraphAttributes
	bool IsSimpleGraph() const;
	bool IsDirectedGraph() const;
	bool IsConnected() const;
	bool IsAcyclic() const;
	bool IsDAG() const;
	bool IsTree() const;
	bool IsBipartite() const;
};
