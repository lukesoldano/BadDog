#pragma once

#include <type_traits>

template<typename T>
concept IsArithmetic = std::is_arithmetic_v<T>;