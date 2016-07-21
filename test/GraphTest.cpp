#include "GraphTest.hpp"

#include <Graph.hpp>

TEST_F(GraphTest, CheckGraphConstructors) {
	Graph
		empty,
		reflexive(Graph::REFLEXIVE),
		five_symmetric(5, Graph::SYMMETRIC);
	ASSERT_EQ(empty.Size(), 0);
	ASSERT_EQ(empty.GetProperties(), Graph::NO_PROPERTIES);
	ASSERT_EQ(reflexive.Size(), 0);
	ASSERT_EQ(five_symmetric.GetNodes().size(), five_symmetric.Size());
	ASSERT_EQ(five_symmetric.Size(), 5);

	ASSERT_TRUE(reflexive.HasProperty(Graph::REFLEXIVE));
	ASSERT_FALSE(reflexive.HasProperty(Graph::SYMMETRIC));
	ASSERT_EQ(five_symmetric.GetProperties(), Graph::SYMMETRIC);

	empty.AddNode();
	ASSERT_EQ(empty.Size(), 1);
}

TEST_F(GraphTest, CheckNodesLinkage) {
	Graph
		simple(5, Graph::NO_PROPERTIES),
		reflexive(5, Graph::REFLEXIVE),
		symmetric(5, Graph::SYMMETRIC);

	for(const Node &it : simple.GetNodes())
		for(const Node &it2 : simple.GetNodes())
			ASSERT_FALSE(it >> it2 || it2 << it);

	for(const Node &it : reflexive.GetNodes())
		ASSERT_TRUE(it >> it && it << it);

	for(Graph *graph : {&simple, &symmetric})
		for(size_t i = 0; i < graph->Size(); ++i)
			graph->Connect(i, (i + 1) % graph->Size());

	for(size_t i = 0; i < simple.Size(); ++i)
		for(size_t j = 0; j < simple.Size(); ++j)
			ASSERT_EQ((i + 1) % simple.Size() == j, simple[i] >> simple[j]);

	for(size_t i = 0; i < symmetric.Size(); ++i)
		for(size_t j = 0; j < symmetric.Size(); ++j)
			ASSERT_EQ((i + 1) % symmetric.Size() == j || i == (j + 1) % symmetric.Size(), symmetric[i] >> symmetric[j]);

	ASSERT_NO_THROW(simple.Print());
	ASSERT_NO_THROW(reflexive.Print());
	ASSERT_NO_THROW(symmetric.Print());
}
