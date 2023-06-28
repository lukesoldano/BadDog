#include <gtest/gtest.h>

#include "ExtendedOptional.hpp"

TEST(ExtendedOptional, ConstructionAndAssignment)
{
   extended_opt<int> opt;
   EXPECT_FALSE(opt.has_value());
   opt = 5;
   EXPECT_TRUE(opt.has_value());
   EXPECT_EQ(opt.value(), 5);
   opt = extended_opt<int>();
   EXPECT_FALSE(opt.has_value());
}

TEST(ExtendedOptional, Map)
{
   extended_opt<int> opt;
   EXPECT_FALSE(opt.has_value());
   auto opt2 = opt.map([](int i) { return i + 1; });
   EXPECT_FALSE(opt2.has_value());
   opt = 5;
   EXPECT_TRUE(opt.has_value());
   EXPECT_EQ(opt.value(), 5);
   opt2 = opt.map([](int i) { return i + 1; });
   EXPECT_TRUE(opt2.has_value());
   EXPECT_EQ(opt2.value(), 6);
}

TEST(ExtendedOptional, AndThen)
{
   extended_opt<int> opt;
   EXPECT_FALSE(opt.has_value());
   auto opt2 = opt.and_then([](int i) { return extended_opt<int>(i + 1); });
   EXPECT_FALSE(opt2.has_value());
   opt = 5;
   EXPECT_TRUE(opt.has_value());
   EXPECT_EQ(opt.value(), 5);
   opt2 = opt.and_then([](int i) { return extended_opt<int>(i + 1); });
   EXPECT_TRUE(opt2.has_value());
   EXPECT_EQ(opt2.value(), 6);
}