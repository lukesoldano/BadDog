#pragma once

#include <string>
#include <type_traits>

template<typename T>
concept IsArithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept IsString = std::is_same_v<T, std::string> || 
                   std::is_same_v<T, const std::string> || 
                   std::is_same_v<T, const std::string&> || 
                   std::is_same_v<T, char> || 
                   std::is_same_v<T, const char> || 
                   std::is_same_v<T, const char&> || 
                   std::is_same_v<T, char*>|| 
                   std::is_same_v<T, const char*>;