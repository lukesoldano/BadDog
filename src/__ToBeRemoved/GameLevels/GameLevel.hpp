// #pragma once

// #include "JsonDefs.hpp"
// #include "StaticEntity.hpp"
// #include "StationaryDynamicEntity.hpp"

// #include <filesystem>
// #include <memory>
// #include <string>
// #include <vector>

// namespace Game 
// {

// // Class is JSON deserializable
// struct Level;
// void from_json(const nlohmann::json& i_json, Level& o_level);

// // @warning This class is not thread safe
// struct Level
// {
//    std::string m_name;
//    size_t m_width;
//    size_t m_height;
//    size_t m_shm_cell_width;
//    size_t m_shm_cell_height;
//    size_t m_border_width;
//    float m_player_start_x;
//    float m_player_start_y;

//    std::vector<StaticEntity> m_static_entities;
//    std::vector<StationaryDynamicEntity> m_stationary_dynamic_entities;

//    Level() noexcept = default;
//    Level(std::filesystem::path&& i_json_file_path);
//    virtual ~Level() noexcept = default;
// };

// } // namespace Game