#include "Edge.hpp"

#include <limits.h>


const Edge::dist_t
	Edge::DIST_UNDEF = -LONG_MAX,
	Edge::DIST_MAX = LONG_MAX,
	Edge::DIST_DEFAULT = 1;

Edge::Edge(mask_t mask, dist_t dist):
	mask(mask), dist(dist)
{}

Edge::~Edge()
{}
