#include <gtest/gtest.h>

#include "ExtendedOptional.hpp"
#include "RandomNumberGenerator.hpp"

#include <set>

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

TEST(RandomNumberGenerator, GenerateIntsWithRange)
{
   RandomNumberGenerator<uint32_t> generator;

   for (auto i=0; i<1000; ++i)
   {
      EXPECT_LE(generator.get_random_number_in_range(0, 10), 10);
      EXPECT_GE(generator.get_random_number_in_range(0, 10), 0);
      EXPECT_LE(generator.get_random_number_in_range(10, 20), 20);
      EXPECT_GE(generator.get_random_number_in_range(10, 20), 10);

      EXPECT_GE(generator.get_random_number_over(0), 0);
      EXPECT_LE(generator.get_random_number_under(10), 10);
   }
}

TEST(RandomNumberGenerator, GenerateFloatsWithRange)
{
   RandomNumberGenerator<float> generator;

   for (auto i=0; i<1000; ++i)
   {
      EXPECT_LE(generator.get_random_number_in_range(0.0f, 10.0f), 10.0f);
      EXPECT_GE(generator.get_random_number_in_range(0.0f, 10.0f), 0.0f);
      EXPECT_LE(generator.get_random_number_in_range(10.0f, 20.0f), 20.0f);
      EXPECT_GE(generator.get_random_number_in_range(10.0f, 20.0f), 10.0f);

      EXPECT_GE(generator.get_random_number_over(0.0f), 0.0f);
      EXPECT_LE(generator.get_random_number_under(10.0f), 10.0f);
   }
}

TEST(RandomNumberGenerator, GenerateUniqueInts)
{
   RandomNumberGenerator<uint32_t> generator;

   const auto MAX_NUM_MATCHES_ALLOWED = 10;
   std::set<uint32_t> values;

   for (auto i=1; i<1000; ++i)
   {
      auto is_unique = values.insert(generator.get_random_number()).second;
      if (false == is_unique && (i - values.size()) > MAX_NUM_MATCHES_ALLOWED)
      {
         FAIL() << "Random number generator is not random enough!";
      }
   }
}

TEST(RandomNumberGenerator, GenerateUniqueFloats)
{
   RandomNumberGenerator<float> generator;

   const auto MAX_NUM_MATCHES_ALLOWED = 10;
   std::set<float> values;

   for (auto i=1; i<1000; ++i)
   {
      auto is_unique = values.insert(generator.get_random_number()).second;
      if (false == is_unique && (i - values.size()) > MAX_NUM_MATCHES_ALLOWED)
      {
         FAIL() << "Random number generator is not random enough!";
      }
   }
}

TEST(RandomNumberGenerator, SeparateIntGeneratorsUnique)
{
   RandomNumberGenerator<uint32_t> generator_one;
   RandomNumberGenerator<uint32_t> generator_two;

   const auto MAX_NUM_MATCHES_ALLOWED = 10;

   auto num_matches = 0;
   for (auto i=0; i<1000; ++i)
   {
      num_matches += (generator_one.get_random_number() == generator_two.get_random_number() ? 1 : 0);
      ASSERT_TRUE(num_matches <= MAX_NUM_MATCHES_ALLOWED) << "Random number generators are not unique!";
   }
}

TEST(RandomNumberGenerator, SeparateFloatGeneratorsUnique)
{
   RandomNumberGenerator<float> generator_one;
   RandomNumberGenerator<float> generator_two;

   const auto MAX_NUM_MATCHES_ALLOWED = 10;

   auto num_matches = 0;
   for (auto i=0; i<1000; ++i)
   {
      num_matches += (generator_one.get_random_number() == generator_two.get_random_number() ? 1 : 0);
      ASSERT_TRUE(num_matches <= MAX_NUM_MATCHES_ALLOWED) << "Random number generators are not unique!";
   }
}