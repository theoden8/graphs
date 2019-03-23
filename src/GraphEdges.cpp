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
	/* if(Is(PSEUDOGRAPH)) */
	/* 	Connect(Size() - 1, Size() - 1); */
}

void Graph::Connect(size_t id1, size_t id2, Edge::dist_t dist, Edge::bandwidth_t bwidth) {
	if(!Is(PSEUDOGRAPH) && id1 == id2)
		throw std::domain_error("cant link a node to itself in irreflexive graph.");

	Edge edge(Edge::NONE, dist, bwidth);
	nodes_[id1] >>= {nodes_[id2], edge};
	if(!Is(DIRECTEDGRAPH))
		nodes_[id1] <<= {nodes_[id2], edge};
}

void Graph::RandomlyConnect() {
	if(Size() == 0)
		return;
	if(Size() == 1) {
		if(Is(PSEUDOGRAPH) && rand() & 1)
			Connect(0, 0);
		return;
	}
	size_t E = Size() * (Size() - 1);
	if(!Is(DIRECTEDGRAPH))
		E /= 2;
	if(Is(PSEUDOGRAPH))
		E += Size();
	size_t connectedness = rand() % E;
	/* printf("|E| == %lu\n", E); */
	for(size_t i = 0; i < Size() - (Is(SIMPLEGRAPH) ? 1 : 0); ++i)
		for(size_t j = (Is(DIRECTEDGRAPH) ? 0 : i + (Is(PSEUDOGRAPH) ? 0 : 1)); j < Size(); ++j) {
			if(!Is(PSEUDOGRAPH) && i == j)
				continue;
			/* printf("[%lu, %lu]\n", i, j); */
			if(rand() % E <= connectedness)
				Connect(i, j);
		}
	/* Print(); */
}

Graph Graph::Random(size_t size) {
	Graph G(size, Graph::SIMPLEGRAPH
			| (rand() & 1) ? PSEUDOGRAPH : 0x00
			| (rand() & 1) ? DIRECTEDGRAPH : 0x00);
	G.RandomlyConnect();
	return G;
}

Node &Graph::operator[] (size_t idx) {
	return nodes_[idx];
}

Node Graph::operator[] (size_t idx) const {
	return nodes_[idx];
}
