#include "Graph.hpp"


void Graph::AddNode() {
	nodes_.push_back(Node(Size() - 1));
	if(I_AM(REFLEXIVE))
		Connect(Size() - 1, Size() - 1);
}

void Graph::Connect(size_t id1, size_t id2) {
	if(!I_AM(REFLEXIVE) && id1 == id2)
		throw std::domain_error("cant link a node to itself in irreflexive graph.");

	nodes_[id1] >>= nodes_[id2];
	if(I_AM(SYMMETRIC))
		nodes_[id1] <<= nodes_[id2];
}
