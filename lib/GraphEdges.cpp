#include "Graph.hpp"
#include "Debug.hpp"

const std::vector <Node> &Graph::GetNodes() const {
	return nodes_;
}

size_t Graph::Size() const {
	return nodes_.size();
}


void Graph::AddNode() {
	nodes_.push_back(Node(Size()));
	if(Is(PSEUDOGRAPH))
		Connect(Size() - 1, Size() - 1);
}

void Graph::Connect(size_t id1, size_t id2, Edge::dist_t dist) {
	if(!Is(PSEUDOGRAPH) && id1 == id2)
		throw std::domain_error("cant link a node to itself in irreflexive graph.");

	nodes_[id1] >>= nodes_[id2];
	if(!Is(DIRECTEDGRAPH))
		nodes_[id1] <<= nodes_[id2];
}


Node &Graph::operator[] (size_t idx) {
	return nodes_[idx];
}

Node Graph::operator[] (size_t idx) const {
	return nodes_[idx];
}
