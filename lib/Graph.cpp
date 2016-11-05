#include <stdexcept>

#include "Graph.hpp"

Graph::Graph():
	nodes_(), properties_(NO_PROPERTIES)
{}

Graph::Graph(Edge::mask_t properties):
	nodes_(), properties_(properties)
{}

Graph::Graph(size_t size, Edge::mask_t properties):
	nodes_(),
	properties_(properties)
{
	for(size_t i = 0; i < size; ++i)
		AddNode();
}

Graph::~Graph()
{}


Edge::mask_t Graph::GetProperties() const {
	return properties_;
}

bool Graph::Is(Edge::mask_t property) const {
	if(property == NO_PROPERTIES && properties_ == 0x00)
		return true;
	return properties_ & INT2MASK(property);
}


void Graph::Print() const {
	printf("Properties: %X\n", GetProperties());
	for(const auto &src : nodes_) {
		printf("%lu :\t", src.id());

		for(const auto &dst : nodes_)
			printf(" %X ", src.at(dst).mask);

		printf("\n");
	}
}
