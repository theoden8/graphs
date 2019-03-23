#pragma once

#include <functional>
#include <optional>

template <typename T> struct assigner {
	std::function <void (T &)> setter;
	std::optional <T> value;
public:
	assigner(std::function <void (T &)> &setter):
		setter(setter)
	{}

	assigner(std::function <void (T &)> &&setter):
		setter(setter)
	{}

	T operator=(T &val) {
		setter(val);
		return (value = val);
	}

	T operator=(T &&val) {
		setter(val);
		return (value = val);
	}

	operator T() {
		if(value) {
			return *value;
		}
		throw std::runtime_error("the assigner holds no value");
	}
};
