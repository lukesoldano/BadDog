#include "GraphicsEngine.hpp"

#include "Logger.hpp"
#include "GameState.hpp"
#include "ProjectDefs.hpp"
#include "RenderInstructionFactory.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <system_error>

using namespace Graphics;

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
   if (std::nullopt == window_optional)
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

   renderer.render(RenderInstructionFactory::get_instruction(background_image_texture,
                                                             SDL_Rect{0, 0, 680, 480},
                                                             SDL_Rect{0, 0, 680, 480}));

   auto& game_state = GameState::instance();
   renderer.set_draw_color(Color::black);
   renderer.render(RenderInstructionFactory::get_instruction(game_state.m_active_entities[0]));
   
   renderer.set_draw_color(Color::red);
   renderer.render(RenderInstructionFactory::get_instruction(game_state.m_static_entities[1]));
   

   
   /////////////////////////////////////////////////////////////////////////////////////////////////

   renderer.render_present();
}