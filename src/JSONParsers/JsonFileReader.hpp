#pragma once

#include "Logger.hpp"
#include "JsonUtilities.hpp"

#include <assert.h>
#include <filesystem>
#include <fstream>
#include <optional>

namespace JSON
{
namespace FileReader
{
   // Declarations
   inline std::optional<nlohmann::json> read_json_file(std::filesystem::path i_json_file) noexcept;
   
   // Definitions
   std::optional<nlohmann::json> read_json_file(std::filesystem::path i_json_file) noexcept
   {
      LOG_MESSAGE("Reading JSON file: " + i_json_file.string());

      if (!Utilities::is_json_file(i_json_file))
      {
         LOG_ERROR("File is not a json file: '" << i_json_file.string() << "'");
         return std::nullopt;
      }

      std::ifstream read_stream(i_json_file);
      if (!read_stream.is_open())
      {
         LOG_ERROR("Failed to open json file: '" << i_json_file.string() << "'");
         return std::nullopt;
      } 

      try
      {
         return nlohmann::json::parse(read_stream);
      }
      catch (nlohmann::json::parse_error& e)
      {
         assert(false && e.what());
         LOG_ERROR("Failed to parse json file: '" << 
                   i_json_file.string() << 
                   "' with error: '" << 
                   e.what() << 
                   "'");
         return std::nullopt;
      }
   }

} // namespace FileReader

} // namespace JSON
