#include <gtest/gtest.h>

#include "split.hpp"

TEST(SplitTest, SplitNumbers) {
    auto list = split("1.2.3", '.');
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list[0], "1");
    EXPECT_EQ(list[1], "2");
    EXPECT_EQ(list[2], "3");
}

TEST(SplitTest, FirstEmpty) {
    auto list = split(".2", '.');
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "");
    EXPECT_EQ(list[1], "2");
}

TEST(SplitTest, LastEmpty) {
    auto list = split("1.", '.');
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "1");
    EXPECT_EQ(list[1], "");
}

TEST(SplitTest, NoDelimiters) {
    auto list = split("str", '.');
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "str");
}

TEST(SplitTest, EmptyString) {
    auto list = split("", '.');
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], "");
}

TEST(SplitTest, TabDelimiter) {
    auto list = split("1\t2", '\t');
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], "1");
    EXPECT_EQ(list[1], "2");
}
