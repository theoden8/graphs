#include "Node.hpp"


void Node::operator>>= (Node &other) {
	ports[other.id()] |= OUTBOUND;
	other.ports[id()] |= INBOUND;
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
					at(other) == MULL
			||
					other.has(*this)
				&&
					other.at(*this) == MULL
		) && (
					at(other) & INBOUND
				&&
					!(other.at(*this) & OUTBOUND)
			||
					at(other) & OUTBOUND
				&&
					!(other.at(*this) & INBOUND)
		)
	);
}


void Node::print(FILE *out) const {
	fprintf(out, "node: %lu\n", id_);
	for(const auto &it : ports)
		fprintf(out, "	%lu : %x\n", it.first, it.second);
}
