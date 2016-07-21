#pragma once

#include <unordered_map>

#define  INBOUND (1 << 0)
#define OUTBOUND (1 << 1)

typedef char mask_t;

struct node_t {
private:
	const size_t id_;
public:
	std::unordered_map <size_t, mask_t> edges;

public:
	node_t(size_t id);
	~node_t();

	size_t id() const;

	void operator>>= (node_t &other);

	const bool operator== (const node_t &other) const;
	const bool operator>> (const node_t &other);
	const bool operator<< (const node_t &other);

	void print() const;
};
