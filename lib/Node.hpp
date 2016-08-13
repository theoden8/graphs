#pragma once

#include <cstdio>
#include <unordered_map>

typedef char mask_t;

class Node {
	const size_t id_;
	std::unordered_map <size_t, mask_t> ports;
public:
	typedef enum {
		MULL,
		INBOUND,
		OUTBOUND
	} PORT_TYPE;

	Node(size_t id);
	~Node();

	size_t id() const;
	bool has(const Node &key) const;
	bool has(const size_t &key) const;
	mask_t at(const Node &key) const;
	mask_t at(const size_t &key) const;
	std::unordered_map <size_t, mask_t> get_ports() const;

	const bool operator== (const Node &other) const;
	const bool operator!= (const Node &other) const;
	const bool operator>> (const Node &other) const;
	const bool operator<< (const Node &other) const;

	void operator>>= (Node &other);
	void operator<<= (Node &other);
	void operator-= (Node &other);
	bool check_pair(const Node &other) const;
	void print(FILE *out = stdout) const;
};
