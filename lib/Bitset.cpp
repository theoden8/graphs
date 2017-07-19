#include "Bitset.hpp"
#include "Debug.hpp"

#include <climits>

const size_t Bitset::u_sz = sizeof(uint64_t) * 8;

Bitset::Bitset(size_t size, bool value):
	size_(size),
	vec((size + u_sz-1) / u_sz, value ? UINT_MAX : 0)
{
	if(value)
		vec[vec.size() - 1] &= ((1 << (size % u_sz)) - 1);
}

size_t Bitset::size() const {
	return size_;
}

bool Bitset::operator[](size_t idx) const {
	return vec[idx / 8] & (1 << (idx % 8 - 1));
}

assigner <bool> Bitset::operator[](size_t idx) {
	auto &&f = [&](bool &x){this->Set(idx, x);};
	return assigner<bool>(f);
}

void Bitset::Set(size_t idx, bool value) {
	vec[idx / u_sz]
		= value
		? (vec[idx / u_sz] | (1 << (idx % u_sz)))
		: (vec[idx / u_sz] & ~(1 << (idx % u_sz)));
}

size_t Bitset::Count() {
	size_t n = 0;
	using T = uint64_t;
	for(T x : vec) {
		x = x - ((x >> 1) & (T)~(T)0/3);                            // temp
		x = (x & (T)~(T)0/15*3) + ((x >> 2) & (T)~(T)0/15*3);       // temp
		x = (x + (x >> 4)) & (T)~(T)0/255*15;                       // temp
		n += (T)(x * ((T)~(T)0/255)) >> (sizeof(T) - 1) * CHAR_BIT; // count
	}
	return n;
}
