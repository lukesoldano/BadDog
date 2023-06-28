#include "GraphicsEngine.hpp"

#include "Camera.hpp"
#include "Logger.hpp"
#include "GameState.hpp"
#include "ProjectDefs.hpp"
#include "RenderInstructionFactory.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <system_error>

// TODO Remove
#include "CollisionDetector.hpp"
//

using namespace Graphics;

namespace
{
   constexpr SDL_FRect SCREEN_CENTER{DEFAULT_WINDOW_WIDTH/2, DEFAULT_WINDOW_HEIGHT/2, 0, 0};
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
   static FileSystem::Path background_image_path{std::string(ASSETS_DIRECTORY) + "/test_background.jpg"};
   static auto background_image_surface = Graphics::Surface::create_from_image(background_image_path).value();
   static auto background_image_texture = renderer.create_texture_from_surface(std::move(background_image_surface)).value();

   static FileSystem::Path kona_image_path{std::string(ASSETS_DIRECTORY) + "/KonaTemp.png"};
   static auto kona_image_surface = Graphics::Surface::create_from_image(kona_image_path).value();
   static auto kona_image_texture = renderer.create_texture_from_surface(std::move(kona_image_surface)).value();

   static Camera camera(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_LEVEL_WIDTH, DEFAULT_LEVEL_HEIGHT);

   auto& game_state = GameState::instance();

   const auto camera_frame = camera.get_frame(game_state.m_active_entities[0]);
   
   // Player position is centered unless near edges
   auto player_camera_position = SCREEN_CENTER;
   player_camera_position.h = 50;
   player_camera_position.w = 50;
   switch(camera_frame.m_x_frame_position)
   {
      case XFramePosition::on_left_edge:
         player_camera_position.x = game_state.m_active_entities[0].x;
         break;
      case XFramePosition::on_right_edge:
         player_camera_position.x = game_state.m_active_entities[0].x - DEFAULT_LEVEL_WIDTH + DEFAULT_WINDOW_WIDTH;
         break;
      case XFramePosition::off_edge: // fall through
      default:
         break; // do nothing
   }

   switch(camera_frame.m_y_frame_position)
   {
      case YFramePosition::on_top_edge:
         player_camera_position.y = game_state.m_active_entities[0].y;
         break;
      case YFramePosition::on_bottom_edge:
         player_camera_position.y =  game_state.m_active_entities[0].y - DEFAULT_LEVEL_HEIGHT + DEFAULT_WINDOW_HEIGHT;
         break;
      case YFramePosition::off_edge: // fall through
      default:
         break; // do nothing
   }

   renderer.render(RenderInstructionFactory::get_instruction(background_image_texture,
                                                             camera_frame.m_rect,
                                                             std::optional<SDL_Rect>()));

   renderer.set_draw_color(Color::black);
   renderer.render(RenderInstructionFactory::get_instruction(kona_image_texture,
                                                             std::nullopt,
                                                             player_camera_position));
   
   renderer.set_draw_color(Color::red);
   for (const auto& entity : game_state.m_static_entities)
   {
      if (Physics::CollisionDetector().are_aabbs_colliding(RECT_TO_FRECT(camera_frame.m_rect), entity.second))
      {
         SDL_FRect render_rect{entity.second.x - camera_frame.m_rect.x,
                               entity.second.y - camera_frame.m_rect.y,
                               entity.second.w,
                               entity.second.h};
         renderer.render(RenderInstructionFactory::get_instruction(render_rect));
      }
   }
   

   
   /////////////////////////////////////////////////////////////////////////////////////////////////

   renderer.render_present();
}