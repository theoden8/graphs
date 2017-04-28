#include "GraphTest.hpp"

#include <Graph.hpp>

TEST_F(GraphTest, CheckGraphConstructors) {
	Graph
		empty,
		reflexive(Graph::PSEUDOGRAPH),
		five_directed(5, Graph::DIRECTEDGRAPH);
	ASSERT_EQ(empty.Size(), 0);
	ASSERT_EQ(empty.GetProperties(), Graph::SIMPLEGRAPH);
	ASSERT_TRUE(empty.Is(Graph::SIMPLEGRAPH));
	ASSERT_FALSE(empty.Is(Graph::PSEUDOGRAPH));
	ASSERT_FALSE(empty.Is(Graph::DIRECTEDGRAPH));

	ASSERT_EQ(reflexive.Size(), 0);
	ASSERT_EQ(five_directed.Size(), 5);
	ASSERT_EQ(five_directed.GetNodes().size(), five_directed.Size());

	ASSERT_TRUE(reflexive.Is(Graph::PSEUDOGRAPH));
	ASSERT_FALSE(reflexive.Is(Graph::DIRECTEDGRAPH));
	ASSERT_EQ(five_directed.GetProperties(), Graph::DIRECTEDGRAPH);
	ASSERT_FALSE(five_directed.Is(Graph::PSEUDOGRAPH));
	ASSERT_TRUE(five_directed.Is(Graph::DIRECTEDGRAPH));

	empty.AddNode();
	ASSERT_EQ(empty.Size(), 1);
}

TEST_F(GraphTest, CheckNodesLinkage) {
	Graph
		simple(5, Graph::SIMPLEGRAPH),
		reflexive(5, Graph::PSEUDOGRAPH),
		directed(5, Graph::DIRECTEDGRAPH);

	for(const Node &it : simple.GetNodes())
		for(const Node &it2 : simple.GetNodes())
			ASSERT_FALSE(it >> it2 || it2 << it);

	for(const Node &it : reflexive.GetNodes())
		ASSERT_TRUE(it >> it && it << it);

	for(Graph *graph : {&simple, &directed})
		for(size_t i = 0; i < graph->Size(); ++i)
			graph->Connect(i, (i + 1) % graph->Size());

	for(size_t i = 0; i < simple.Size(); ++i)
		for(size_t j = 0; j < simple.Size(); ++j)
			if(j == (i + 1) % simple.Size() || i == (j + 1) % directed.Size())
				ASSERT_TRUE(simple[i] >> simple[j]);
			else
				ASSERT_FALSE(simple[i] >> simple[j]);

	for(size_t i = 0; i < directed.Size(); ++i)
		for(size_t j = 0; j < directed.Size(); ++j)
			if(j == ((i + 1) % directed.Size()))
				ASSERT_TRUE(directed[i] >> directed[j]);
			else
				ASSERT_FALSE(directed[i] >> directed[j]);

	ASSERT_NO_THROW(simple.Print());
	ASSERT_NO_THROW(reflexive.Print());
	ASSERT_NO_THROW(directed.Print());
}
