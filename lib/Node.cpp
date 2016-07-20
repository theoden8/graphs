#include "Node.hpp"

#include <cstdio>

node_t::node_t(const size_t id):
	id_(id), edges()
{}


node_t::~node_t() {
}


size_t node_t::id() const {
	return id_;
}

void node_t::join(node_t &other) {
	edges[other.id()] |= OUTBOUND;
	other.edges[id()] |= INBOUND;
}



const bool node_t::operator== (const node_t &other) const {
	return id_ == other.id();
}

const bool node_t::operator>> (const node_t &other) {
	return edges[other.id()] & OUTBOUND;
}

const bool node_t::operator<< (const node_t &other) {
	return edges[other.id()] & INBOUND;
}


void node_t::print() const {
	printf("node: %lu\n", id_);
	for(const auto &it : edges)
		printf("	%lu : %x\n", it.first, it.second);
}
