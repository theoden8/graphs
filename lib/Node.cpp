#include "Node.hpp"

#include <cstdio>
#include <cassert>

Node::Node(const size_t id):
	id_(id),
	ports()
{}

Node::~Node()
{}


size_t Node::id() const {
	return id_;
}

bool Node::has(const Node &key) const {
	return has(key.id());
}

bool Node::has(const size_t &key) const {
	return ports.find(key) != ports.end();
}

Edge Node::at(const Node &key) const {
	return at(key.id());
}

Edge Node::at(const size_t &key) const {
	if(has(key)) {
		const Edge val = ports.at(key);
		assert(!val.is_none());
		return val;
	}
	return Edge(Edge::NONE);
}

size_t Node::deg() const {
	size_t ret = 0;
	for(const auto &[edge_id, edge] : get_ports())
		if(edge.is_out())
			++ret;
	return ret;
}

size_t Node::deg_in() const {
	size_t ret = 0;
	for(const auto &[edge_id, edge] : get_ports())
		if(edge.is_in())
			++ret;
	return ret;
}

size_t Node::deg_out() const {
	return deg();
}

std::unordered_map <size_t, Edge> Node::get_ports() const {
	return ports;
}


const bool Node::operator== (const Node &other) const {
	return id_ == other.id();
}

const bool Node::operator!= (const Node &other) const {
	return !(*this == other);
}

const bool Node::operator>> (const Node &other) const {
	return at(other).is_out();
}

const bool Node::operator<< (const Node &other) const {
	return other >> *this;
}
