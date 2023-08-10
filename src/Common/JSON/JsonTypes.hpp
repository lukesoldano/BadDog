#pragma once

#include "ProjectConcepts.hpp"

#include <nlohmann/json.hpp>

#include <type_traits>

namespace JSON
{

using json = nlohmann::json;

template <IsString T>
bool get_json_value(const json& i_json, T i_key, auto&& o_value) noexcept
{
   const auto it = i_json.find(i_key);
   if (it == i_json.end()) return false;

   // TODO: Add some type safety checks here

   o_value = it->get<std::remove_cvref_t<decltype(o_value)>>();
   return true;
}

} // namespace JSON