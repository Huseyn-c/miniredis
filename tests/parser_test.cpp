#include <gtest/gtest.h>
#include "parser.h"

TEST(ParserTest, SplitsBySpaces) {
    std::vector<std::string> expected = {"SET", "name", "Huseyn"};
    EXPECT_EQ(tokenize("SET name Huseyn"), expected);
}

TEST(ParserTest, IgnoresExtraSpaces) {
    std::vector<std::string> expected = {"GET", "name"};
    EXPECT_EQ(tokenize("  GET    name  "), expected);
}

TEST(ParserTest, EmptyLineGivesEmptyVector) {
    EXPECT_TRUE(tokenize("").empty());
}