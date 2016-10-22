#pragma once

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
	static const dist_t
		DIST_UNDEF,
		DIST_MAX,
		DIST_DEFAULT;

	mask_t mask;
	dist_t dist;

	Edge(mask_t mask = MULL, dist_t dist = 1);
	virtual ~Edge();
};
