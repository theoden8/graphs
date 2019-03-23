#include "Node.hpp"
#include "Debug.hpp"

void Node::operator>>= (std::pair <Node &, Edge> conn) {
	auto &[node, edge] = conn;
	if(!has(node))
		ports[node.id()] = edge;
	ports[node.id()].set_outbound();
	if(!node.has(*this))
		node.ports[id()] = edge;
	node.ports[id()].set_inbound();
	/* printf("CONNECTING %lu to %lu\n", id(), node.id()), print(), node.print(); */
}

void Node::operator<<= (std::pair <Node &, Edge> conn) {
	auto &[node, edge] = conn;
	node >>= {*this, edge};
}

void Node::operator-= (Node &other) {
	ports.erase(other.id());
	other.ports.erase(id());
}


bool Node::check_pair(const Node &other) const {
	return !(
		(
			has(other) && at(other).is_none()
			|| other.has(*this) && other.at(*this).is_none()
		)
		&&
		(
			at(other).is_in() && !other.at(*this).is_out()
			|| at(other).is_out() && !other.at(*this).is_in()
		)
	);
}


void Node::print(FILE *out) const {
	fprintf(out, "node: %lu\n", id_);
	for(const auto &it : ports) {
		fprintf(out, "	%lu : { %x, %ld }\n", it.first, it.second.mask, it.second.dist);
	}
}
