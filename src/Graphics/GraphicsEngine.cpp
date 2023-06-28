#include "GraphicsEngine.hpp"

#include "Camera.hpp"
#include "Logger.hpp"
#include "GameState.hpp"
#include "ProjectDefs.hpp"
#include "RenderInstructionFactory.hpp"
#include "SpriteSheet.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <system_error>

// TODO Remove
#include "CollisionDetector.hpp"
//

using namespace Graphics;

namespace
{
   const FRect SCREEN_CENTER{Game::Settings::DEFAULT_WINDOW_WIDTH/2, 
                             Game::Settings::DEFAULT_WINDOW_HEIGHT/2, 
                             0, 
                             0};
}

void GraphicsEngine::initialize()
{
   LOG_MESSAGE("Enter GraphicsEngine::initialize()");

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Initialize SDL2
   //// Set texture filtering to linear
   if (SDL_FALSE == SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
   {
      LOG_WARNING("Failed to set linear texture filtering option");
   }

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Initialize SDL2_image
   int supported_image_types = IMG_INIT_PNG;
   if (0 == (supported_image_types & IMG_Init(supported_image_types)))
   {
      LOG_ERROR("Failed to initialize the SDL2_image library, IMG Error: " << IMG_GetError());
      throw std::system_error(EACCES, 
                              std::generic_category(), 
                              "Failed call to IMG_Init(), IMG Error: " + std::string(IMG_GetError()));
   }

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Create Window
   auto window_optional = Window::create();
   if (!window_optional.has_value())
   {
      LOG_ERROR("Failed to create Window!");
      throw std::system_error(EACCES, std::generic_category(), "Failed to create Window!");
   }

   m_window = std::make_unique<Window>(std::move(window_optional.value()));

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // Preload textures
   // const FileSystem::Path background_image_path{std::string(ASSETS_DIRECTORY) + "/windowsxp.png"};
   // auto background_image_surface_optional = Graphics::Surface::create_from_image(background_image_path);
   // if (std::nullopt == background_image_surface_optional)
   // {
   //    LOG_ERROR("Failed to load background image to surface!");
   //    throw std::system_error(EACCES, 
   //                            std::generic_category(), 
   //                            "Failed to load background image to surface!");
   // }

   // auto background_image_texture_optional = m_window->get_renderer().create_texture_from_surface(std::move(background_image_surface_optional.value()));
   // if (std::nullopt == background_image_texture_optional)
   // {
   //    LOG_ERROR("Failed to load background image to texture!");
   //    throw std::system_error(EACCES, 
   //                            std::generic_category(), 
   //                            "Failed to load background image to texture!");
   // }

   LOG_MESSAGE("Exit GraphicsEngine::initialize()");
}

// Tears down objects in reverse order
void GraphicsEngine::teardown()
{
   LOG_MESSAGE("Enter GraphicsEngine::teardown()");

   if (nullptr != m_window)
   {
      m_window->teardown();
   }

   IMG_Quit();

   LOG_MESSAGE("Exit GraphicsEngine::teardown()");
}

void GraphicsEngine::render()
{
   if (nullptr == m_window)
   {
      LOG_ERROR("m_window is no longer valid!");
      throw std::system_error(EACCES, std::generic_category(), "m_window is no longer valid!");
   }

   auto& renderer = m_window->get_renderer();

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO: Remove, this is just test bed code (Enter your test bed code here)
   static std::filesystem::path background_image_path{std::string(ASSETS_DIRECTORY) + "/test_background.jpg"};
   static auto background_image_surface = Graphics::Surface::create_from_image(background_image_path).value();
   static auto background_image_texture = renderer.create_texture_from_surface(std::move(background_image_surface)).value();

   static std::filesystem::path kona_image_path{std::string(ASSETS_DIRECTORY) + "/Kona-Walk-Sheet.png"};
   static auto kona_image_surface = Graphics::Surface::create_from_image(kona_image_path).value();
   static auto kona_image_texture = renderer.create_texture_from_surface(std::move(kona_image_surface)).value();
   static SpriteSheet<1, 8> kona_sprite_sheet(std::move(kona_image_texture));
   static auto kona_frame = 0;

   static Camera camera(Game::Settings::DEFAULT_WINDOW_WIDTH, 
                        Game::Settings::DEFAULT_WINDOW_HEIGHT, 
                        Game::Settings::DEFAULT_LEVEL_WIDTH, 
                        Game::Settings::DEFAULT_LEVEL_HEIGHT);

   auto& game_state = Game::State::instance();

   const auto camera_frame = camera.get_frame(game_state.m_active_entities[0]);
   
   // Player position is centered unless near edges
   auto player_camera_position = SCREEN_CENTER;
   player_camera_position.w = game_state.m_active_entities[0].w;
   player_camera_position.h = game_state.m_active_entities[0].h;
   switch(camera_frame.m_x_frame_position)
   {
      case XFramePosition::on_left_edge:
         player_camera_position.x = game_state.m_active_entities[0].x;
         break;
      case XFramePosition::on_right_edge:
         player_camera_position.x = game_state.m_active_entities[0].x - 
                                    Game::Settings::DEFAULT_LEVEL_WIDTH + 
                                    Game::Settings::DEFAULT_WINDOW_WIDTH;
         break;
      case XFramePosition::off_edge:
         // camera position gives centered position of frame, adjust by half width for actual
         // entity position
         player_camera_position.x -= (game_state.m_active_entities[0].w / 2.0f);
         break;
      default:
         break; // do nothing
   }

   switch(camera_frame.m_y_frame_position)
   {
      case YFramePosition::on_top_edge:
         player_camera_position.y = game_state.m_active_entities[0].y;
         break;
      case YFramePosition::on_bottom_edge:
         player_camera_position.y =  game_state.m_active_entities[0].y - 
                                     Game::Settings::DEFAULT_LEVEL_HEIGHT + 
                                     Game::Settings::DEFAULT_WINDOW_HEIGHT;
         break;
      case YFramePosition::off_edge:
         // camera position gives centered position of frame, adjust by half height for actual
         // entity position
         player_camera_position.y -= (game_state.m_active_entities[0].h / 2.0f);
         break;
      default:
         break; // do nothing
   }

   // Render background
   renderer.render(RenderInstructionFactory::get_instruction(background_image_texture,
                                                             camera_frame.m_level_position.to_rect(),
                                                             std::optional<Rect>()));

   // renderer.render(RenderInstructionFactory::get_instruction(player_camera_position));
   static int temp = 0;
   if (++temp % 10 == 0)
   {
      temp = 0;
      if (++kona_frame == 8) kona_frame = 0;
   }

   SDL_RendererFlip flip = game_state.m_player_entity_rotation == 180.0f ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

   renderer.render(RenderInstructionFactory::get_instruction(kona_sprite_sheet.get_texture(),
                                                             kona_sprite_sheet.get_frame(0, kona_frame),
                                                             player_camera_position,
                                                             game_state.m_player_entity_rotation,
                                                             flip));

   for (const auto& entityId : game_state.m_spatial_hash_map.get_neighbors(camera_frame.m_level_position))
   {
      if (Physics::CollisionDetector().are_aabbs_colliding(camera_frame.m_level_position, 
                                                           game_state.m_static_entities[entityId]))
      {
         renderer.set_draw_color(game_state.m_static_entities[entityId].m_rgba_color);
         FRect render_rect{game_state.m_static_entities[entityId].x - camera_frame.m_level_position.x,
                           game_state.m_static_entities[entityId].y - camera_frame.m_level_position.y,
                           game_state.m_static_entities[entityId].w,
                           game_state.m_static_entities[entityId].h};
         renderer.render(RenderInstructionFactory::get_instruction(render_rect));
      }
   }
   
   // Render game progress bar
   Rect progress_bar_rect{Game::Settings::DEFAULT_WINDOW_WIDTH/4, 30, Game::Settings::DEFAULT_WINDOW_WIDTH/2, 30};
   renderer.set_draw_color(Color::white);
   renderer.render(RenderInstructionFactory::get_instruction(progress_bar_rect));

   progress_bar_rect.x += 5;
   progress_bar_rect.y += 5;
   progress_bar_rect.w -= 10;
   progress_bar_rect.h -= 10;

   progress_bar_rect.w *= (game_state.m_remaining_game_time_ms / 10000.0f);
   renderer.set_draw_color(Color::black);
   renderer.render(RenderInstructionFactory::get_instruction(progress_bar_rect));

   
   /////////////////////////////////////////////////////////////////////////////////////////////////

   renderer.render_present();
}