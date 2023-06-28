#include <gtest/gtest.h>

// @TODO Provide a real test
TEST(Renderer, TODO) 
{
   // For Colby: Use expect when a test can fail without crashing all proceeding tests, use ASSERT
   // when an absolute condition must be reached - should be an equivalent for any check between
   // EXPECT and ASSERT
   EXPECT_TRUE(true);
   ASSERT_TRUE(true);
   EXPECT_FALSE(false);
   ASSERT_FALSE(false);

   // USE NE, EQ, LT, GT comparisons vs EXPECT_TRUE(1 > 0) as the failed test (if it fails) will 
   // give you both values and show you how it failed, vs 1 > 0 which will just state false
   auto my_var = 1;
   EXPECT_NE(0, my_var);
   ASSERT_NE(0, my_var);

   EXPECT_EQ(1, my_var);
   ASSERT_EQ(1, my_var);

   // There's a lot more to GTest like mocks, etc, but for now we can just worry about basics
}

