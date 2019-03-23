#include "Edge.hpp"

const Edge::dist_t
	Edge::DIST_UNDEF = -LONG_MAX,
	Edge::DIST_MAX = LONG_MAX,
	Edge::DIST_DEFAULT = 1;

const Edge::bandwidth_t
	Edge::BWIDTH_UNDEF = Edge::BWIDTH_MAX,
	Edge::BWIDTH_MAX = LONG_MAX,
	Edge::BWIDTH_DEFAULT = 1;

Edge::Edge(mask_t mask, dist_t dist, bandwidth_t bwidth):
	mask(mask), dist(dist), bwidth(bwidth)
{}

Edge::~Edge()
{}

void Edge::set_inbound() {
	mask |= INBOUND;
}

void Edge::set_outbound() {
	mask |= OUTBOUND;
}

const bool Edge::is_none() const {
	return mask == NONE;
}

const bool Edge::is_in() const {
	return mask & INBOUND;
}

const bool Edge::is_out() const {
	return mask & OUTBOUND;
}
