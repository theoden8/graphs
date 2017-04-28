#pragma once

#include <cstdlib>
#include <stdexcept>
#include <vector>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CODE_LOCATION "\033[1m" __FILE__ "\033[0m::\033[93m" TOSTRING(__LINE__) "\033[0m"
#define CONDITION_TOSTR(CONDITION) " ( \033[1;4m" STRINGIFY(CONDITION) "\033[0m )"

#define ASSERT_DOMAIN(CONDITION) { \
	if(!(CONDITION)) { \
		throw std::domain_error("\033[1;91mdomain_error\033[0m" CODE_LOCATION CONDITION_TOSTR(CONDITION));\
	} \
}
