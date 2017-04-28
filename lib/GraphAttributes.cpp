#include "Graph.hpp"
#include "Debug.hpp"

#include <numeric>

bool Graph::IsSimpleGraph() const {
	if(Is(SIMPLEGRAPH))
		return true;
	return false;
}

bool Graph::IsDirectedGraph() const {
	return Is(DIRECTEDGRAPH);
}

bool Graph::IsConnected() const {
	if(Size() == 0)
		return true;
	std::vector <bool> discovered(Size(), false);
	discovered[0] = true;
	for(label_t i = 0; i < Size(); ++i) {
		const Node &nd = nodes_[i];
		if(!discovered[i])
			return false;
		for(const auto &it : nd.get_ports()) {
			if(it.first > i)
				discovered[it.first] = true;
		}
	}
	return true;
}

bool Graph::IsAcyclic() const {
	if(Size() == 0)
		return true;
	//
	return false;
}

bool Graph::IsDAG() const {
	return IsDirectedGraph() && IsAcyclic();
}

bool Graph::IsTree() const {
	if(!IsSimpleGraph())
		return false;
	bool seen_root = false;
	for(const auto &nd : GetNodes()) {
		size_t ins = nd.deg_in();
		if(ins != 1) {
			if(ins == 0 && !seen_root)
				seen_root=true;
			else
				return false;
		}
	}
	return true;
}

bool Graph::IsBipartite() const {
	return false;
}
