#include "Node.hpp"


void Node::operator>>= (Node &other) {
	Edge
		&outb = ports[other.id()],
		&inb = other.ports[id()];
	outb.mask |= Edge::OUTBOUND;
	outb.dist = Edge::DIST_DEFAULT;
	inb.mask |= Edge::INBOUND;
}

void Node::operator<<= (Node &other) {
	other >>= *this;
}

void Node::operator-= (Node &other) {
	ports.erase(other.id());
	other.ports.erase(id());
}


bool Node::check_pair(const Node &other) const {
	return !(
		(
					has(other)
				&&
					at(other).mask == Edge::MULL
			||
					other.has(*this)
				&&
					other.at(*this).mask == Edge::MULL
		) && (
					at(other).mask & Edge::INBOUND
				&&
					!(other.at(*this).mask & Edge::OUTBOUND)
			||
					at(other).mask & Edge::OUTBOUND
				&&
					!(other.at(*this).mask & Edge::INBOUND)
		)
	);
}


void Node::print(FILE *out) const {
	fprintf(out, "node: %lu\n", id_);
	for(const auto &it : ports) {
		fprintf(out, "	%lu : { %x, %ld }\n", it.first, it.second.mask, it.second.dist);
	}
}
