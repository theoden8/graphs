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

mask_t Node::at(const Node &key) const {
	return at(key.id());
}

mask_t Node::at(const size_t &key) const {
	if(has(key)) {
		const mask_t val = ports.at(key);
		assert(val != MULL);
		return val;
	}
	return MULL;
}


const bool Node::operator== (const Node &other) const {
	return id_ == other.id();
}

const bool Node::operator!= (const Node &other) const {
	return !(operator==(other));
}

const bool Node::operator>> (const Node &other) const {
	if(ports.count(other.id()))
		return ports.at(other.id()) & OUTBOUND;
	return false;
}

const bool Node::operator<< (const Node &other) const {
	return other >> *this;
}

