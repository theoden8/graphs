#pragma once

#include <limits.h>
#include <stdio.h>

class Edge {
public:
	typedef char mask_t;
	typedef enum {
		MULL,
		INBOUND,
		OUTBOUND
	} PORT_TYPE;

	typedef long dist_t;
	typedef size_t bandwidth_t;
	static const dist_t
		DIST_UNDEF,
		DIST_MAX,
		DIST_DEFAULT;
	static const bandwidth_t
		BWIDTH_UNDEF,
		BWIDTH_MAX,
		BWIDTH_DEFAULT;

	mask_t mask;
	dist_t dist;
	bandwidth_t bwidth;

	Edge(mask_t mask = MULL, dist_t dist = 1, bandwidth_t bwidth = LONG_MAX);
	virtual ~Edge();
};
