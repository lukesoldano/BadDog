#pragma once

#include "ProjectConcepts.hpp"

#include <limits>
#include <random>
#include <type_traits>

template<IsArithmetic T>
class RandomNumberGenerator 
{
   std::mt19937 m_generator;

public:

   RandomNumberGenerator();

   T get_random_number();

   T get_random_number_in_range(T i_min, T i_max);
   T get_random_number_over(T i_min);             
   T get_random_number_under(T i_max);
   
};

template<IsArithmetic T>
RandomNumberGenerator<T>::RandomNumberGenerator() 
{
   static std::mt19937::result_type seed;
   seed += 1;
   m_generator.seed(seed);
}

template<IsArithmetic T>
T RandomNumberGenerator<T>::get_random_number() 
{
   return get_random_number_in_range(std::numeric_limits<T>::min(), 
                                     std::numeric_limits<T>::max());
}

template<IsArithmetic T>
T RandomNumberGenerator<T>::get_random_number_in_range(T i_min, T i_max) 
{
   if constexpr(std::is_integral<T>::value) 
   {
      std::uniform_int_distribution<T> distribution(i_min, i_max);
      return distribution(m_generator);
   } 
   else if constexpr(std::is_floating_point<T>::value) 
   {
      std::uniform_real_distribution<T> distribution(i_min, i_max);
      return distribution(m_generator);
   }
}

template<IsArithmetic T>
T RandomNumberGenerator<T>::get_random_number_over(T i_min) 
{
   const auto num = get_random_number_in_range(i_min, std::numeric_limits<T>::max());
   return num == i_min ? num + 1 : num;
}

template<IsArithmetic T>
T RandomNumberGenerator<T>::get_random_number_under(T i_max) 
{
   const auto num = get_random_number_in_range(std::numeric_limits<T>::min(), i_max);
   return num == i_max ? num - 1 : num;
}