#pragma once

#include <limits.h>
#include <stdio.h>

class Edge {
public:
	typedef char mask_t;
	typedef enum {
		NONE,
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
public:
	mask_t mask;
	dist_t dist;
	bandwidth_t bwidth;
public:
	Edge(mask_t mask = NONE, dist_t dist = 1, bandwidth_t bwidth = LONG_MAX);
	virtual ~Edge();
	void set_inbound();
	void set_outbound();
	const bool is_none() const;
	const bool is_in() const;
	const bool is_out() const;
};
