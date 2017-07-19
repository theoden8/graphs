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

TEST_F(GraphTest, BellmanFordTest) {
	Graph G(10, Graph::PSEUDOGRAPH | Graph::DIRECTEDGRAPH);
	G.Connect(0, 3, 10);
	G.Connect(0, 4, 5);
	G.Connect(0, 5, 20);
	G.Connect(3, 9, 5);
	G.Connect(4, 9, 5);
	G.Connect(5, 9, 5);
	auto &&d = G.bellman_ford(0);
	ASSERT_EQ(d[0], 0);
	ASSERT_EQ(d[1], Edge::DIST_UNDEF);
	ASSERT_EQ(d[2], Edge::DIST_UNDEF);
	ASSERT_EQ(d[3], 10);
	ASSERT_EQ(d[4], 5);
	ASSERT_EQ(d[5], 20);
	ASSERT_EQ(d[6], Edge::DIST_UNDEF);
	ASSERT_EQ(d[7], Edge::DIST_UNDEF);
	ASSERT_EQ(d[8], Edge::DIST_UNDEF);
	ASSERT_EQ(d[9], 10);
}

TEST_F(GraphTest, DijkstraTest) {
	Graph G(10, Graph::PSEUDOGRAPH | Graph::DIRECTEDGRAPH);
	G.Connect(0, 0, 1);
	G.Connect(0, 1, 1);
	G.Connect(1, 2, 2);
	G.Connect(2, 3, 3);
	G.Connect(3, 4, 4); // 10

	G.Connect(0, 2, 2); // 2

	G.Connect(3, 5, 2); // 7
	G.Connect(0, 5, 9); // 9

	G.Connect(5, 7, 2);
	G.Connect(5, 9, 2); // 9
	G.Connect(7, 9, 1); // 11

	auto &&d = G.dijkstra(0);

	ASSERT_EQ(d[0], 0);
	ASSERT_EQ(d[1], 1);
	ASSERT_EQ(d[2], 2);
	ASSERT_EQ(d[3], 5);
	ASSERT_EQ(d[4], 9);
	ASSERT_EQ(d[5], 7);
	ASSERT_EQ(d[6], Edge::DIST_UNDEF);
	ASSERT_EQ(d[7], 9);
	ASSERT_EQ(d[8], Edge::DIST_UNDEF);
	ASSERT_EQ(d[9], 9);
}

TEST_F(GraphTest, DistShortestPathTest) {
	size_t no_tests = 100;
	size_t max_size = 100;
	for(size_t i = 0; i < no_tests; ++i) {
		size_t size = rand() % max_size + 1;
		Graph H = Graph::Random(size);
		size_t start = rand() % size;
		ASSERT_TRUE(H.dijkstra(start) == H.bellman_ford(start));
		/* auto &&d = H.dijkstra(start); auto &&f = H.bellman_ford(start); */
		/* if(d != f) { */
		/* 	H.Print(); */
		/* 	for(auto&it:d)std::cout<<it<<" ";std::cout<<std::endl; */
		/* 	for(auto&it:f)std::cout<<it<<" ";std::cout<<std::endl; */
		/* 	std::cout << std::endl; */
		/* } */
	}
}
