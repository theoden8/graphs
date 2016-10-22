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
	return ports.count(key.id());
}

bool Node::has(const size_t &key) const {
	return ports.count(key);
}

Edge Node::at(const Node &key) const {
	return at(key.id());
}

Edge Node::at(const size_t &key) const {
	if(has(key)) {
		const Edge val = ports.at(key);
		assert(val.mask != Edge::MULL);
		return val;
	}
	return Edge(Edge::MULL);
}

std::unordered_map <size_t, Edge> Node::get_ports() const {
	return ports;
}


const bool Node::operator== (const Node &other) const {
	return id_ == other.id();
}

const bool Node::operator!= (const Node &other) const {
	return !(operator==(other));
}

const bool Node::operator>> (const Node &other) const {
	if(ports.count(other.id()))
		return ports.at(other.id()).mask & Edge::OUTBOUND;
	return false;
}

const bool Node::operator<< (const Node &other) const {
	return other >> *this;
}

