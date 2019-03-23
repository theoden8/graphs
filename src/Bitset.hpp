#pragma once

#include <vector>
#include <cstdlib>
#include <cstdint>

#include "Assigner.hpp"

class Bitset {
	std::vector <uint64_t> vec;
	size_t size_;
	static const size_t u_sz;
public:
	Bitset(size_t size = 0, bool value = 0);
	size_t size() const;
	bool operator[](size_t idx) const;
	assigner <bool> operator[](size_t idx);
	void Set(size_t idx, bool value = true);
	size_t Count();
};
