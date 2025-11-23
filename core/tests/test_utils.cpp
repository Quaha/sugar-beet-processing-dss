#include <gtest/gtest.h>

#include "utils.hpp"

TEST(GetRandomDouble, CanUseFunction) {
	EXPECT_NO_THROW(GetRandomDouble(0.0, 1.0));
}

TEST(GetRandomDouble, ReturnsValueInRange) {
	const double min_value = -3.5;
	const double max_value = +7.3;

	for (int test_case = 0; test_case < 10'000; ++test_case) {
		double value = GetRandomDouble(min_value, max_value);
		EXPECT_GT(value, min_value);
		EXPECT_LT(value, max_value);
	}
}