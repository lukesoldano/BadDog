#pragma once

#include <nlohmann/json.hpp>

#include <filesystem>
#include <type_traits>

namespace JSON
{
namespace Utilities
{
   
////////////////////////////////////////////////////////////////////////////////////////////////////
// Declarations
inline bool is_json_file(const std::filesystem::path& i_file_path) noexcept;

// template <typename T>
inline bool get_json_value(const nlohmann::json& i_json, 
                           const std::string& i_key, 
                           auto& o_value) noexcept;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions
bool is_json_file(const std::filesystem::path& i_file_path) noexcept
{
   return i_file_path.extension() == ".json";
}

bool get_json_value(const nlohmann::json& i_json, 
                    const std::string& i_key, 
                    auto& o_value) noexcept
{
   const auto it = i_json.find(i_key);
   if (it == i_json.end()) return false;

   o_value = it->get<std::remove_cvref_t<decltype(o_value)>>();
   return true;
}

} // namespace Utilities

} // namespace JSON