#include "NodeTest.hpp"

#include <Node.hpp>

Edge simple_edge(Edge::NONE, Edge::DIST_DEFAULT);

TEST_F(NodeTest, CheckingConstructorsGettersAndEqOperator) {
	static const size_t x = 1, y = 2;
	Node a(x), b(x), c(y);

	ASSERT_EQ(a, b);
	ASSERT_NE(a, c);
	ASSERT_NE(b, c);

	ASSERT_EQ(a.id(), x);
	ASSERT_EQ(b.id(), x);
	ASSERT_EQ(c.id(), y);

	a >>= {b, simple_edge};
	ASSERT_NO_THROW(a.print());
	ASSERT_NO_THROW(b.print());
}

TEST_F(NodeTest, CheckingJoiningNodes) {
	static const size_t x = 0, y = 1, z = 2;

	Node a(x), b(y), c(z);

	ASSERT_FALSE(a >> b);
	ASSERT_FALSE(b >> b);
	ASSERT_FALSE(c >> b);

	ASSERT_FALSE(b >> a);
	ASSERT_FALSE(b >> b);

	a >>= {b, simple_edge};
	ASSERT_TRUE(a.has(b));
	ASSERT_TRUE(b.has(a));
	ASSERT_TRUE(a.check_pair(b));
	b <<= {c, simple_edge};
	ASSERT_TRUE(b.check_pair(c));

	ASSERT_EQ(a >> b, b << a);
	ASSERT_NE(a >> b, b >> a);

	ASSERT_TRUE(a >> b);
	ASSERT_FALSE(a >> c);
	ASSERT_TRUE(b << c);
	ASSERT_FALSE(b >> c);

	a -= b;
	ASSERT_FALSE(a >> b);
}
