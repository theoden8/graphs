#pragma once

#include <vector>

#include "Node.hpp"

#define GRAPH_NO_PROPERTIES 0x00
#define GRAPH_REFLEXIVE (1 << 0)
#define GRAPH_SYMMETRIC (1 << 1)

class Graph {
	mask_t properties_;
	std::vector <node_t> nodes_;
public:
	Graph();
	Graph(mask_t properties);
	Graph(size_t size, mask_t properties);

	~Graph();

	bool HasProperty(mask_t property) const;

	void AddNode();
	void Connect(size_t id1, size_t id2);

	node_t &operator[] (size_t idx);
	const node_t operator[] (size_t idx) const;

	void Print() const;
private:
	/* data */
};
