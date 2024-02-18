//
// Created by tosiek on 18.02.24.
//

#include <gtest/gtest.h>
#include "../src/library.hpp"

TEST(HelloTest, BasicAssertions) {
    EXPECT_EQ(2 + 3, az::hello());
}

