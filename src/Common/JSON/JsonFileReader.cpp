#include "JsonFileReader.hpp"

#include "Logger.hpp"
#include "ProjectMacros.hpp"

#include <fstream>
#include <iostream>

std::string JSON::FileInfo::to_string() const
{
   std::ostringstream os;
   os << "Path: " <<
         m_file_path << 
         ", Type: " << 
         m_type <<
         ", Creation Date: " <<
         m_creation_date << 
         ", Last Updated: " <<
         m_last_updated_date;
   return os.str();
}

bool JSON::FileReader::is_json_file(const std::filesystem::path& i_file_path) noexcept
{
   constexpr auto JSON_FILE_EXTENSION = ".json";
   return i_file_path.extension() == JSON_FILE_EXTENSION;
}

extended_opt<std::pair<JSON::FileInfo, JSON::json>> JSON::FileReader::read_json_file(std::filesystem::path i_json_file) noexcept
{
   using namespace JSON;

   LOG_MESSAGE("Reading JSON file: " + i_json_file.string());

   {
      std::error_code error_code;
      if (! std::filesystem::exists(i_json_file, error_code))
      {
         LOG_ERROR("File does not exist: '" << i_json_file.string() << "'");
         return std::nullopt;
      }
   }

   if (! is_json_file(i_json_file))
   {
      LOG_ERROR("File is not a json file: '" << i_json_file.string() << "'");
      return std::nullopt;
   }

   std::ifstream read_stream(i_json_file);
   if (! read_stream.is_open())
   {
      LOG_ERROR("Failed to open json file: '" << i_json_file.string() << "'");
      return std::nullopt;
   } 

   json json_object;
   try
   {  
      json_object = json::parse(read_stream);
   }
   catch (nlohmann::json::parse_error& e)
   {
      read_stream.close();
      LOG_ERROR("Failed to parse json file: '" << 
                i_json_file.string() << 
                "' with error: '" << 
                e.what() << 
                "'");
      return std::nullopt;
   }

   FileInfo file_info;
   if (! get_json_value(json_object, "file_info", file_info))
   {
      LOG_ERROR("Failed to read 'type' from json file: '" << i_json_file.string() << "'");
      return std::nullopt;
   }

   file_info.m_file_path = i_json_file.string();

   return std::pair<FileInfo, json>{ std::move(file_info), std::move(json_object) };
}