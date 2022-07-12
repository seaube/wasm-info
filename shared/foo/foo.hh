#pragma once

#include <string>

namespace example {
	inline auto foo() {
		using namespace std::string_literals;
		return "foo"s;
	}
}
