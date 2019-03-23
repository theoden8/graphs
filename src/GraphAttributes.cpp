#include "Graph.hpp"
#include "Debug.hpp"

#include <queue>
#include <numeric>

bool Graph::IsSimpleGraph() const {
	if(Is(SIMPLEGRAPH))
		return true;
	for(auto &nd : GetNodes())
		for(auto &[out_id, e] : nd.get_ports())
			if(e.is_in() != e.is_out())
				return false;
	return true;
}

bool Graph::IsDirectedGraph() const {
	return Is(DIRECTEDGRAPH);
}

bool Graph::IsPseudoGraph() const {
	return Is(PSEUDOGRAPH);
}

bool Graph::IsWeaklyConnected() const {
	if(Size() == 0)
		return true;
	list_t <bool> discovered(Size(), false);
	label_t start = Size() - 1;
	size_t no_found = 0;
	discovered[(++no_found, start)] = true;
	std::queue <label_t> spiral;
	spiral.push(start);
	while(!spiral.empty()) {
		const Node &nd = GetNodes()[spiral.front()];
		const size_t u = nd.id();
		spiral.pop();
		for(const auto &[v, e] : nd.get_ports()) {
			if(!discovered[v]) {
				discovered[(++no_found, v)] = true;
				spiral.push(v);
			}
		}
	}
	return no_found == Size();
}

bool Graph::IsStronglyConnected() const {
	if(!Is(DIRECTEDGRAPH))
		return IsWeaklyConnected();
	if(Size() == 0)
		return true;
	size_t start = 0;
	auto &&discovered = dfs(start); size_t no_found = 0;
	std::queue <label_t> spiral;
	for(size_t i = 0; i < Size(); ++i)
		if(discovered[(++no_found, i)])
			spiral.push(i);
	puts("IS STRONGLY CONNECTED: BEGIN");
	for(auto it:discovered)printf("%d ", it?1:0); puts("");
	while(!spiral.empty()) {
		const Node &nd = GetNodes()[spiral.front()];
		const size_t u = nd.id();
		printf("Popping %ld\n", u);
		spiral.pop();
		for(const auto &[v, e] : nd.get_ports()) {
			if(e.is_in() && !discovered[v]) {
				discovered[(++no_found, v)] = true;
				spiral.push(v);
				printf("Pushing %ld\n", v);
			}
		}
	}
	puts("IS STRONGLY CONNECTED: END");
	return no_found == Size();
}

bool Graph::IsConnected() const {
	return IsWeaklyConnected();
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
