#pragma once

#include <vector>

#include "Node.hpp"

#define INT2MASK(INT) (1 << ((INT) - 1))

class Graph {
	mask_t properties_;
	std::vector <Node> nodes_;
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
	bool HasProperty(mask_t property) const;
	std::vector <Node> GetNodes() const;
	size_t Size() const;

	Node &operator[] (size_t idx);
	const Node operator[] (size_t idx) const;

	void AddNode();
	void Connect(size_t id1, size_t id2);

	void Print() const;
private:
	/* data */
};
