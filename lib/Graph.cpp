#include <stdexcept>

#include "Graph.hpp"

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

bool Graph::Is(mask_t property) const {
	return properties_ & INT2MASK(property);
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
