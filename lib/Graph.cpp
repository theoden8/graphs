#include <stdexcept>

#include "Graph.hpp"

#define I_AM(property) HasProperty(property)

Graph::Graph():
	nodes_(), properties_(NO_PROPERTIES)
{}

Graph::Graph(mask_t properties):
	nodes_(), properties_(properties)
{}

Graph::Graph(size_t size, mask_t properties):
	nodes_(),
	properties_(properties)
{
	for(size_t i = 0; i < size; ++i)
		AddNode();
}

Graph::~Graph()
{}


mask_t Graph::GetProperties() const {
	return properties_;
}

bool Graph::HasProperty(mask_t property) const {
	return properties_ & INT2MASK(property);
}

std::vector <Node> Graph::GetNodes() const {
	return nodes_;
}

size_t Graph::Size() const {
	return nodes_.size();
}


Node &Graph::operator[] (size_t idx) {
	return nodes_[idx];
}

const Node Graph::operator[] (size_t idx) const {
	return nodes_[idx];
}


void Graph::AddNode() {
	nodes_.push_back(Node(Size()));
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


void Graph::Print() const {
	printf("Properties: %X\n", GetProperties());
	for(const auto &src : nodes_) {
		printf("%lu :\t", src.id());

		for(const auto &dst : nodes_)
			printf(" %X ", src.at(dst));

		printf("\n");
	}
}
