#include "gtest/gtest.h"

#include <string>

#include "shared/foo.hh"

TEST(Foo, FooResultCorrect) {
	using namespace std::string_literals;
	EXPECT_EQ(example::foo(), "foo"s);
}
