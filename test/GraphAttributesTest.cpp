#include <vector>

#include "GraphTest.hpp"

#include <Graph.hpp>

TEST_F(GraphTest, GraphBasicAttributesTest) {
	Graph empty_simple(100, Graph::SIMPLEGRAPH);
	ASSERT_TRUE(empty_simple.IsSimpleGraph());
	ASSERT_FALSE(empty_simple.IsDirectedGraph());
	ASSERT_FALSE(empty_simple.IsPseudoGraph());

	Graph empty_directed(100, Graph::DIRECTEDGRAPH);
	ASSERT_TRUE(empty_directed.IsSimpleGraph());
	ASSERT_TRUE(empty_directed.IsDirectedGraph());
	ASSERT_FALSE(empty_directed.IsPseudoGraph());

	Graph directed_but_simple(100, Graph::DIRECTEDGRAPH);
	directed_but_simple.Connect(0, 1);
	ASSERT_FALSE(directed_but_simple.IsSimpleGraph());
	directed_but_simple.Connect(1, 0);
	ASSERT_TRUE(directed_but_simple.IsSimpleGraph());
}

TEST_F(GraphTest, GraphIsConnectedTest) {
	Graph H(3, Graph::PSEUDOGRAPH | Graph::DIRECTEDGRAPH);
	srand(time(NULL));
	H.RandomlyConnect();
	Graph G(100, Graph::SIMPLEGRAPH);
	for(size_t i = 0; i < G.Size() - 2; ++i)
		G.Connect(i, i + 1);
	ASSERT_FALSE(G.IsConnected());
	G.Connect(G.Size() - 2, G.Size() - 1);
	ASSERT_TRUE(G.IsConnected());
}

TEST_F(GraphTest, GraphConnectednessTest) {
	size_t no_tests = 1000;
	size_t max_size = 10;
	for(size_t i = 0; i < no_tests; ++i) {
		size_t size = rand() % max_size + 1;
		Graph H = Graph::Random(size);
		if(H.IsStronglyConnected()) {
			H.Print();
			ASSERT_TRUE(H.IsWeaklyConnected());
		}
		size_t start = rand() % size;
		auto &&dfs = H.dfs(start);
		bool seen_false = false;
		for(size_t i = 0; i < dfs.size() && !seen_false; ++i)
			if(!dfs[i])
				seen_false = true;
		if(seen_false)
			continue;
		ASSERT_TRUE(H.IsStronglyConnected());
	}
}
