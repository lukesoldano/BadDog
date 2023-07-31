#include "GraphicsEngine.hpp"

// #include "Camera.hpp"
#include "Logger.hpp"
// #include "GameState.hpp"
#include "ProjectMacros.hpp"
// #include "RenderInstructionFactory.hpp"
// #include "SpriteSheet.hpp"

#include "SDL.h"
#include "SDL_image.h"

// #include <system_error>

// // TODO Remove
// #include "CollisionDetector.hpp"
// //

using namespace Graphics;

// namespace
// {
//    const FRect SCREEN_CENTER{Game::Settings::DEFAULT_WINDOW_WIDTH/2, 
//                              Game::Settings::DEFAULT_WINDOW_HEIGHT/2, 
//                              0, 
//                              0};
// }

void Engine::initialize()
{
   LOG_MESSAGE("Enter Engine::initialize()");

   // Initialize SDL2
   if (SDL_FALSE == SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
   {
      LOG_WARNING("Failed to set linear texture filtering option");
   }

   // Initialize SDL2_image
   int supported_image_types = IMG_INIT_PNG;
   if (0 == (supported_image_types & IMG_Init(supported_image_types)))
   {
      ASSERT(std::string("Failed to initialize the SDL2_image library, IMG Error: ") + 
             IMG_GetError());
   }

   // Create Window
   m_window = std::make_unique<Window>();

//    /////////////////////////////////////////////////////////////////////////////////////////////////
//    // Preload textures
//    // const FileSystem::Path background_image_path{std::string(ASSETS_DIRECTORY) + "/windowsxp.png"};
//    // auto background_image_surface_optional = Graphics::Surface::create_from_image(background_image_path);
//    // if (std::nullopt == background_image_surface_optional)
//    // {
//    //    LOG_ERROR("Failed to load background image to surface!");
//    //    throw std::system_error(EACCES, 
//    //                            std::generic_category(), 
//    //                            "Failed to load background image to surface!");
//    // }

//    // auto background_image_texture_optional = m_window->get_renderer().create_texture_from_surface(std::move(background_image_surface_optional.value()));
//    // if (std::nullopt == background_image_texture_optional)
//    // {
//    //    LOG_ERROR("Failed to load background image to texture!");
//    //    throw std::system_error(EACCES, 
//    //                            std::generic_category(), 
//    //                            "Failed to load background image to texture!");
//    // }

   LOG_MESSAGE("Exit Engine::initialize()");
}

// Tears down objects in reverse order
void Engine::teardown()
{
   LOG_MESSAGE("Enter Engine::teardown()");

   m_window.reset();

   IMG_Quit();

   LOG_MESSAGE("Exit Engine::teardown()");
}

void Engine::process()
{
   if (nullptr == m_window) ASSERT("m_window is no longer valid!");

   auto& renderer = m_window->get_renderer();

//    /////////////////////////////////////////////////////////////////////////////////////////////////
//    // TODO: Remove, this is just test bed code (Enter your test bed code here)
//    static std::filesystem::path background_image_path{std::string(ASSETS_DIRECTORY) + "/test_background.jpg"};
//    static auto background_image_surface = Graphics::Surface::create_from_image(background_image_path).value();
//    static auto background_image_texture = renderer.create_texture_from_surface(std::move(background_image_surface)).value();

//    static std::filesystem::path kona_image_path{std::string(ASSETS_DIRECTORY) + "/Kona-Walk-Sheet.png"};
//    static auto kona_image_surface = Graphics::Surface::create_from_image(kona_image_path).value();
//    static auto kona_image_texture = renderer.create_texture_from_surface(std::move(kona_image_surface)).value();
//    static SpriteSheet<1, 8> kona_sprite_sheet(std::move(kona_image_texture));
//    static auto kona_frame = 0;

//    static std::filesystem::path dog_bone_image_path{std::string(ASSETS_DIRECTORY) + "/DogBone.png"};
//    static auto dog_bone_image_surface = Graphics::Surface::create_from_image(dog_bone_image_path).value();
//    static auto dog_bone_image_texture = renderer.create_texture_from_surface(std::move(dog_bone_image_surface)).value();

//    static Camera camera(Game::Settings::DEFAULT_WINDOW_WIDTH, 
//                         Game::Settings::DEFAULT_WINDOW_HEIGHT, 
//                         Game::Settings::DEFAULT_LEVEL_WIDTH, 
//                         Game::Settings::DEFAULT_LEVEL_HEIGHT);

//    auto& game_state = Game::State::instance();

//    const auto camera_frame = camera.get_frame(game_state.m_player_entity);
   
//    // Player position is centered unless near edges
//    auto player_camera_position = SCREEN_CENTER;
//    player_camera_position.w = game_state.m_player_entity.w;
//    player_camera_position.h = game_state.m_player_entity.h;
//    switch(camera_frame.m_x_frame_position)
//    {
//       case XFramePosition::on_left_edge:
//          player_camera_position.x = game_state.m_player_entity.x;
//          break;
//       case XFramePosition::on_right_edge:
//          player_camera_position.x = game_state.m_player_entity.x - 
//                                     Game::Settings::DEFAULT_LEVEL_WIDTH + 
//                                     Game::Settings::DEFAULT_WINDOW_WIDTH;
//          break;
//       case XFramePosition::off_edge:
//          // camera position gives centered position of frame, adjust by half width for actual
//          // entity position
//          player_camera_position.x -= (game_state.m_player_entity.w / 2.0f);
//          break;
//       default:
//          break; // do nothing
//    }

//    switch(camera_frame.m_y_frame_position)
//    {
//       case YFramePosition::on_top_edge:
//          player_camera_position.y = game_state.m_player_entity.y;
//          break;
//       case YFramePosition::on_bottom_edge:
//          player_camera_position.y =  game_state.m_player_entity.y - 
//                                      Game::Settings::DEFAULT_LEVEL_HEIGHT + 
//                                      Game::Settings::DEFAULT_WINDOW_HEIGHT;
//          break;
//       case YFramePosition::off_edge:
//          // camera position gives centered position of frame, adjust by half height for actual
//          // entity position
//          player_camera_position.y -= (game_state.m_player_entity.h / 2.0f);
//          break;
//       default:
//          break; // do nothing
//    }

//    // Render background
//    renderer.render(RenderInstructionFactory::get_instruction(background_image_texture,
//                                                              camera_frame.m_level_position.to_rect(),
//                                                              std::optional<Rect>()));

//    renderer.render(RenderInstructionFactory::get_instruction(player_camera_position));
//    static int temp = 0;
//    if (++temp % 10 == 0)
//    {
//       temp = 0;
//       if (++kona_frame == 8) kona_frame = 0;
//    }

//    SDL_RendererFlip flip = game_state.m_player_entity_rotation == 180.0f ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

//    renderer.render(RenderInstructionFactory::get_instruction(kona_sprite_sheet.get_texture(),
//                                                              kona_sprite_sheet.get_frame(0, kona_frame),
//                                                              player_camera_position,
//                                                              game_state.m_player_entity_rotation,
//                                                              flip));

//    for (const auto& entity_id : game_state.m_spatial_hash_map.get_neighbors(camera_frame.m_level_position))
//    {
//       if (Game::PLAYER_ENTITY_ID == entity_id) continue;
//       else if (game_state.m_static_entities.contains(entity_id) && 
//                Physics::CollisionDetector().are_aabbs_colliding(camera_frame.m_level_position, 
//                                                                 game_state.m_static_entities[entity_id].get_hitbox()))
//       {
//          renderer.render(RenderInstructionFactory::get_static_entity_instruction(camera_frame, 
//                                                                                  game_state.m_static_entities[entity_id]));
//       }
//       else if (game_state.m_stationary_dynamic_entities.contains(entity_id) && 
//                Physics::CollisionDetector().are_aabbs_colliding(camera_frame.m_level_position, 
//                                                                 game_state.m_stationary_dynamic_entities[entity_id].get_hitbox()))
//       {
//          auto render_space = game_state.m_stationary_dynamic_entities[entity_id].get_hitbox();
//          render_space.x -= camera_frame.m_level_position.x;
//          render_space.y -= camera_frame.m_level_position.y;
//          renderer.render(RenderInstructionFactory::get_instruction(dog_bone_image_texture,
//                                                                    std::nullopt,
//                                                                    render_space));
//       }
//    }
   
//    // Render game progress bar
//    Rect progress_bar_rect{Game::Settings::DEFAULT_WINDOW_WIDTH/4, 30, Game::Settings::DEFAULT_WINDOW_WIDTH/2, 30};
//    renderer.set_draw_color(Color::white);
//    renderer.render(RenderInstructionFactory::get_instruction(progress_bar_rect));

//    progress_bar_rect.x += 5;
//    progress_bar_rect.y += 5;
//    progress_bar_rect.w -= 10;
//    progress_bar_rect.h -= 10;

//    progress_bar_rect.w *= (game_state.m_remaining_game_time_ms / 10000.0f);
//    renderer.set_draw_color(Color::black);
//    renderer.render(RenderInstructionFactory::get_instruction(progress_bar_rect));

   
//    /////////////////////////////////////////////////////////////////////////////////////////////////

   renderer.render_present();
}