#include <cmath>
#include <unordered_map>

#include "GraphTest.hpp"

#include <Graph.hpp>

TEST_F(GraphTest, BFSTest) {
	const size_t N = 100;
	std::cout << std::endl;
	Graph
		numbers(N, Graph::REFLEXIVE | Graph::SYMMETRIC);
	for(size_t i = 2; i < N; ++i) {
		for(size_t j = i + i; j < N; j += i) {
			numbers.Connect(j - i, j);
			ASSERT_TRUE(numbers[j - i] >> numbers[j]);
		}
	}
	numbers.Print();
	/* for(size_t i = 2; i * (i + 2) < N - 1; ++i) { */
	/* 	std::unordered_map <size_t, int> result = Graph::bfs(i); */
	/* 	std::map <size_t, int> factors_i(); */
	/* 	size_t i2 = i; */
	/* 	while(i2 != 1) { */
	/* 		for(size_t x = 0; x * (x + 2) < i; ++x) */
	/* 			if(i2 / x * x == i2) */
	/* 				factors_i[x] = (factors_i.count(x) == 0) ? 1 : factors_i[x] + 1; */
	/* 	} */
	/* } */
	std::vector <int> bfs = numbers.bfs(2);
	for(size_t i = 0; i < N; ++i)
		std::cout << i << '\t' << bfs[i] << std::endl;
}
