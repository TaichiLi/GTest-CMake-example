#include <cstdio>
#include <gtest/gtest.h>
#include "fib.h"
#include "fac.h"

int add(int a, int b)
{
    return a + b;
}

TEST(addtest, HandleNoneZeroInput)
{
    EXPECT_EQ(14 , add(4, 10));
    EXPECT_EQ(-2, add(-3, 1));
    EXPECT_EQ(0, fib(0));
    EXPECT_EQ(1, fib(1));
    EXPECT_EQ(1, fib(2));
    EXPECT_EQ(1, fac(0));
    EXPECT_EQ(1, fac(1));
    EXPECT_EQ(120, fac(5));
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
