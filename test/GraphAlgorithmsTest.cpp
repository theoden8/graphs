#include <vector>

#include "GraphTest.hpp"

#include <Graph.hpp>

#define NUMIDX(x) (x - 1)
TEST_F(GraphTest, BFSTest) {
	const size_t N = 100;
	Graph
		numbers(N, Graph::REFLEXIVE | Graph::SYMMETRIC);

	for(size_t i = 2; i < N; ++i) {
		for(size_t j = i * i; j - i <= N; j *= i) {
			numbers.Connect(NUMIDX(i), NUMIDX(j - i));
		}
	}

	std::vector <Graph::dist_t>
		bfs1 = numbers.bfs(NUMIDX(1)),
		bfs2 = numbers.bfs(NUMIDX(2));
	for(size_t i = 0; i < N; ++i) {
		const int val = (i == 0) ? 0 : Graph::UNDEFINED;
		ASSERT_EQ(val, bfs1[i]);
	}

	for(int i = 0; i < bfs2.size(); ++i) {
		std::cout << i + 1 << " : " << bfs2[i] << std::endl;
	}
	ASSERT_EQ(0, bfs2[NUMIDX(2)]);
	ASSERT_EQ(Graph::UNDEFINED, bfs2[NUMIDX(5)]); // no way
	ASSERT_EQ(1, bfs2[NUMIDX(6)]); // 2 6=(8-2)
	ASSERT_EQ(2, bfs2[NUMIDX(3)]); // 2 6=(8-2)=(9-3)=6 3
	ASSERT_EQ(Graph::UNDEFINED, bfs2[NUMIDX(42)]);
	for(size_t i = 4; i < N; i *= 2) {
		ASSERT_EQ(Graph::UNDEFINED, bfs2[NUMIDX(i)]);
	}
}
