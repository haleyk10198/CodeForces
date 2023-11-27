#include "main.hxx"
#include <gtest/gtest.h>
#include <vector>

using namespace ::r910::problemB;

TEST(R910ProblemB, SampleTestCases) {
    EXPECT_EQ(1, solve(std::vector{1, 3, 2}));
    EXPECT_EQ(0, solve(std::vector{1, 2, 3, 4}));
    EXPECT_EQ(3, solve(std::vector{3, 2, 1}));
    EXPECT_EQ(9, solve(std::vector{1, 4, 4, 3, 5, 7, 6}));
}

TEST(R910ProblemB, RepeatBig) {
    constexpr ::r910::problemB::size_t MAX_SIZE = 2e5;
    constexpr int MAX_VALUE = 1e9;

    std::vector<int> input(MAX_SIZE, MAX_VALUE);
    input.back() = 1;

    constexpr ::r910::problemB::size_t EXPECTED_OP = (MAX_VALUE - 1) * (MAX_SIZE - 1);
    EXPECT_EQ(EXPECTED_OP, solve(input));
}

TEST(R910ProblemB, ChunkTwice) {
    auto actual = {9, 3, 1, 8};
    auto input = actual | std::views::reverse;
    EXPECT_EQ(7, solve(input));
}
