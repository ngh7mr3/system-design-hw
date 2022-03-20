#include <gtest/gtest.h>

TEST(test_case, example_test)
{
    EXPECT_EQ(42, 42);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}