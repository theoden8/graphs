#pragma once

#include <vector>
#include <unordered_map>

#include "Node.hpp"

#define INT2MASK(INT) (1 << ((INT) - 1))

class Graph {
	typedef std::vector <Node> nodes_t;
	const mask_t properties_;
	nodes_t nodes_;
public:
	typedef enum {
		NO_PROPERTIES,
		REFLEXIVE,
		SYMMETRIC
	} PROPERTY;

	Graph();
	Graph(mask_t properties);
	Graph(size_t size, mask_t properties);
	~Graph();

	mask_t GetProperties() const;
	bool Is(mask_t property) const;
	nodes_t GetNodes() const;
	size_t Size() const;

	Node &operator[] (size_t idx);
	Node operator[] (size_t idx) const;

	void Print() const;

	void AddNode();
	void Connect(size_t id1, size_t id2);

// GraphAlgorithms
	static const int UNDEFINED;
	std::vector <int> bfs(const size_t from) const;
};
