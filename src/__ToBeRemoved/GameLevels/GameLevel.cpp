// #include "GameLevel.hpp"

// #include "JsonFileReader.hpp"
// #include "ProjectDefs.hpp"

// using namespace Game;

// void Game::from_json(const nlohmann::json& i_json, Level& o_level)
// {
//    o_level.m_name = i_json.at("m_name").get<std::string>();
//    o_level.m_width = i_json.at("m_width").get<size_t>();
//    o_level.m_height = i_json.at("m_height").get<size_t>();
//    o_level.m_shm_cell_width = i_json.at("m_shm_cell_width").get<size_t>();
//    o_level.m_shm_cell_height = i_json.at("m_shm_cell_height").get<size_t>();
//    o_level.m_border_width = i_json.at("m_border_width").get<size_t>();
//    o_level.m_player_start_x = i_json.at("m_player_start_x").get<float>();
//    o_level.m_player_start_y = i_json.at("m_player_start_y").get<float>();
//    o_level.m_static_entities = i_json.at("m_static_entities").get<std::vector<StaticEntity>>();
//    o_level.m_stationary_dynamic_entities = i_json.at("m_stationary_dynamic_entities").get<std::vector<StationaryDynamicEntity>>();     
// }

// Level::Level(std::filesystem::path&& i_json_file_path)
// {
//    using namespace JSON;

//    auto json = FileReader::read_json_file(i_json_file_path);
//    CHECK_CONDITION(json.has_value());
//    if (json) *this = json.value().at(Keys::LEVEL_INFO_OBJECT).get<Level>();
// }