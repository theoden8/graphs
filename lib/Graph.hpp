#pragma once

#include <vector>
#include <unordered_map>

#include "Node.hpp"

#define INT2MASK(INT) (1 << ((INT) - 1))

class Graph {
protected:
	typedef std::vector <Node> nodes_t;
	const Edge::mask_t properties_;
	nodes_t nodes_;
public:

	typedef enum {
		NO_PROPERTIES,
		REFLEXIVE,
		DIRECTED
	} PROPERTY;

	Graph();
	Graph(Edge::mask_t properties);
	Graph(size_t size, Edge::mask_t properties);
	~Graph();

	Edge::mask_t GetProperties() const;
	bool Is(Edge::mask_t property) const;
	nodes_t GetNodes() const;
	size_t Size() const;

	Node &operator[] (size_t idx);
	Node operator[] (size_t idx) const;

	void Print() const;

	void AddNode();
	void Connect(size_t id1, size_t id2, Edge::dist_t dist = Edge::DIST_DEFAULT);

// GraphAlgorithms
	static const Edge::dist_t UNDEFINED;
	std::vector <Edge::dist_t> bfs(const size_t from) const;
	std::vector <bool> dfs(const size_t from) const;
	std::vector <Edge::dist_t> dijkstra(const size_t from) const;
};
