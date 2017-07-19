#pragma once

#include <cstdio>
#include <unordered_map>

#include "Edge.hpp"

class Node {
protected:
	const size_t id_;
	std::unordered_map <size_t, Edge> ports;
public:
	Node(size_t id);
	~Node();

	size_t id() const;
	bool has(const Node &key) const;
	bool has(const size_t &key) const;
	Edge at(const Node &key) const;
	Edge at(const size_t &key) const;
	size_t deg() const;
	size_t deg_in() const;
	size_t deg_out() const;
	std::unordered_map <size_t, Edge> get_ports() const;

	const bool operator== (const Node &other) const;
	const bool operator!= (const Node &other) const;
	const bool operator>> (const Node &other) const;
	const bool operator<< (const Node &other) const;

	void operator>>= (std::pair <Node &, Edge> conn);
	void operator<<= (std::pair <Node &, Edge> conn);
	void operator-= (Node &other);
	bool check_pair(const Node &other) const;
	void print(FILE *out = stdout) const;
};
