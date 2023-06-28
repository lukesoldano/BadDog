#pragma once

#include <functional>
#include <optional>

// An optional with functional add ons to chain together operations
// Idea derived from: https://blog.tartanllama.xyz/optional-expected/
template <typename T>
class extended_opt : public std::optional<T>
{
public:

   extended_opt() = default;
   extended_opt(auto&& args...) : 
      std::optional<T>(std::forward<decltype(args)>(args)) {}
   extended_opt(const extended_opt&) = default;
   extended_opt(extended_opt&&) = default;

   virtual ~extended_opt() = default;

   extended_opt& operator=(const extended_opt&) = default;
   extended_opt& operator=(extended_opt&&) = default;
        
   // For a chained function that will never return a nullopt
   extended_opt<T> map(std::function<T(const T&)> lambda) const
   {
      if (!std::optional<T>::has_value()) return std::nullopt;
      return lambda(std::optional<T>::value());
   }
    
   // For a chained function that may return a nullopt
   extended_opt<T> and_then(std::function<extended_opt<T>(const T&)> lambda) const
   {
      if (!std::optional<T>::has_value()) return std::nullopt;
      return lambda(std::optional<T>::value());
   }

};