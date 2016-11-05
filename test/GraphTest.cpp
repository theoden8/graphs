#include "GraphTest.hpp"

#include <Graph.hpp>

TEST_F(GraphTest, CheckGraphConstructors) {
	Graph
		empty,
		reflexive(Graph::REFLEXIVE),
		five_directed(5, Graph::DIRECTED);
	ASSERT_EQ(empty.Size(), 0);
	ASSERT_EQ(empty.GetProperties(), Graph::NO_PROPERTIES);
	ASSERT_TRUE(empty.Is(Graph::NO_PROPERTIES));
	ASSERT_FALSE(empty.Is(Graph::REFLEXIVE));
	ASSERT_FALSE(empty.Is(Graph::DIRECTED));

	ASSERT_EQ(reflexive.Size(), 0);
	ASSERT_EQ(five_directed.Size(), 5);
	ASSERT_EQ(five_directed.GetNodes().size(), five_directed.Size());

	ASSERT_TRUE(reflexive.Is(Graph::REFLEXIVE));
	ASSERT_FALSE(reflexive.Is(Graph::DIRECTED));
	ASSERT_EQ(five_directed.GetProperties(), Graph::DIRECTED);
	ASSERT_FALSE(five_directed.Is(Graph::REFLEXIVE));
	ASSERT_TRUE(five_directed.Is(Graph::DIRECTED));

	empty.AddNode();
	ASSERT_EQ(empty.Size(), 1);
}

TEST_F(GraphTest, CheckNodesLinkage) {
	Graph
		simple(5, Graph::NO_PROPERTIES),
		reflexive(5, Graph::REFLEXIVE),
		directed(5, Graph::DIRECTED);

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
