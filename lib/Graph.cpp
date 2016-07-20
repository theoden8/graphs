#include "Graph.hpp"

Graph::Graph():
	nodes_(), properties_(0)
{}

Graph::Graph(char properties):
	nodes_(), properties_(properties)
{}

Graph::Graph(size_t size, char properties):
	nodes_(), properties_(properties)
{
	for(size_t i = 0; i < size; ++i)
		AddNode();
}


Graph::~Graph() {
}


void Graph::AddNode() {
	nodes_.push_back(node_t(nodes_.size()));
}

void Graph::Connect(size_t id1, size_t id2) {
	if(~properties_ & GRAPH_REFLEXIVE
		&& id1 == id2
	)
	{
		return;
	}

	nodes_[id1].join(nodes_[id2]);
	if(properties_ & GRAPH_SYMMETRIC) {
		nodes_[id2].join(nodes_[id1]);
	}
}


node_t &Graph::operator[] (size_t idx) {
	return nodes_[idx];
}

const node_t Graph::operator[] (size_t idx) const {
	return nodes_[idx];
}


void Graph::Print() const {
	printf("properties: %X\n", properties_);
	for(const auto &src : nodes_) {
		printf("%lu :\t", src.id());
		for(const auto &dst : nodes_) {
			char mask = (src.edges.find(dst.id()) == src.edges.end()) ? NULL : src.edges.at(dst.id());
			printf(" %X ", mask);
		}
		printf("\n");
	}
}
