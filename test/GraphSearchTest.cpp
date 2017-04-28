#include <vector>

#include "GraphTest.hpp"

#include <Graph.hpp>

#define NUMIDX(x) (x - 1)
TEST_F(GraphTest, BFSTest) {
	const size_t N = 100;
	Graph numbers(N, Graph::PSEUDOGRAPH);
	for(size_t i = 2; i < N; ++i) {
		for(size_t j = i * i; j - i <= N; j *= i) {
			numbers.Connect(NUMIDX(i), NUMIDX(j - i));
		}
	}

	std::vector <Edge::dist_t>
		&&bfs1 = numbers.bfs(NUMIDX(1)),
		&&bfs2 = numbers.bfs(NUMIDX(2));
	for(size_t i = 0; i < N; ++i) {
		const Edge::dist_t val = (i == NUMIDX(1)) ? 0 : Edge::DIST_UNDEF;
		ASSERT_EQ(val, bfs1[i]);
	}

	ASSERT_EQ(0, bfs2[NUMIDX(2)]);
	ASSERT_EQ(Edge::DIST_UNDEF, bfs2[NUMIDX(5)]); // no way
	ASSERT_EQ(1, bfs2[NUMIDX(6)]); // 2 6=(8-2)
	ASSERT_EQ(2, bfs2[NUMIDX(3)]); // 2 6=(8-2)=(9-3)=6 3
	ASSERT_EQ(Edge::DIST_UNDEF, bfs2[NUMIDX(42)]);
	for(size_t i = 4; i < N; i *= 2) {
		ASSERT_EQ(Edge::DIST_UNDEF, bfs2[NUMIDX(i)]);
	}
}
#undef NUMIDX

TEST_F(GraphTest, BFSBidirTest) {
	const size_t N = 100;
	Graph numbers(N, Graph::PSEUDOGRAPH);
	for(size_t i = 0; i < N; ++i) {
		numbers.Connect(i, i);
		if(i < N - 2)
			numbers.Connect(i, i + 2);
	}

	ASSERT_EQ(numbers.bfs_bidirectional(0, 2), 1);
	ASSERT_EQ(numbers.bfs_bidirectional(0, 1), Edge::DIST_UNDEF);
	ASSERT_EQ(numbers.bfs_bidirectional(0, 4), 2);
	ASSERT_EQ(numbers.bfs_bidirectional(0, 98), 49);
}

TEST_F(GraphTest, DFSTest) {
	Graph G(1000, Graph::PSEUDOGRAPH | Graph::DIRECTEDGRAPH);
	for(size_t i = 2; i < G.Size(); ++i) {
		G.Connect(i, i / 2);
		if(i * 2 < G.Size())
			G.Connect(i, i * 2);
	}

	std::vector <bool> &&g_dfs = G.dfs(64);
	for(size_t i = 1; i < G.Size(); i <<= 1) {
		ASSERT_TRUE(g_dfs[i]);
	}

	g_dfs = G.dfs(55);
	ASSERT_TRUE(g_dfs[27]);
	ASSERT_TRUE(g_dfs[880]);
	ASSERT_TRUE(g_dfs[13]);
	ASSERT_TRUE(g_dfs[6]);
	ASSERT_FALSE(g_dfs[999]);
	ASSERT_FALSE(g_dfs[997]);
}

TEST_F(GraphTest, DijkstraTest) {
	Graph
		g(10, Graph::PSEUDOGRAPH | Graph::DIRECTEDGRAPH);
}
