#include "GameGraphics.hpp"

#include "Logger.hpp"
#include "ProjectDefs.hpp"
#include "RenderInstructionFactory.hpp"
#include "GlobalState.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <system_error>

using namespace Graphics;

void GameGraphics::initialize()
{
   LOG_MESSAGE("Enter GameGraphics::initialize()");

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
   const FileSystem::Path background_image_path{std::string(ASSETS_DIRECTORY) + "/windowsxp.png"};
   auto background_image_surface_optional = Graphics::Surface::create_from_image(background_image_path);
   if (std::nullopt == background_image_surface_optional)
   {
      LOG_ERROR("Failed to load background image to surface!");
      throw std::system_error(EACCES, 
                              std::generic_category(), 
                              "Failed to load background image to surface!");
   }

   auto background_image_texture_optional = m_window->get_renderer().create_texture_from_surface(std::move(background_image_surface_optional.value()));
   if (std::nullopt == background_image_texture_optional)
   {
      LOG_ERROR("Failed to load background image to texture!");
      throw std::system_error(EACCES, 
                              std::generic_category(), 
                              "Failed to load background image to texture!");
   }

   GlobalState::Instance().m_background_texture = std::make_unique<Texture>(std::move(background_image_texture_optional.value()));

   LOG_MESSAGE("Exit GameGraphics::initialize()");
}

// Tears down objects in reverse order
void GameGraphics::teardown()
{
   LOG_MESSAGE("Enter GameGraphics::teardown()");

   GlobalState::Instance().m_background_texture.reset();

   if (nullptr != m_window)
   {
      m_window->teardown();
   }

   IMG_Quit();

   LOG_MESSAGE("Exit GameGraphics::teardown()");
}

void GameGraphics::render()
{
   if (nullptr == m_window)
   {
      LOG_ERROR("m_window is no longer valid!");
      throw std::system_error(EACCES, std::generic_category(), "m_window is no longer valid!");
   }

   auto& renderer = m_window->get_renderer();

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO: Remove, this is just test bed code (Enter your test bed code here)
   renderer.render(RenderInstructionFactory::get_instruction(*GlobalState::Instance().m_background_texture.get(),
                                                             {0, 0, 680, 480}));
   
   /////////////////////////////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////////////////////////////////////
   // TODO REMOVE THIS  
   const auto& current_dog_state = GlobalState::Instance().m_current_dog_state;
   renderer.render(RenderInstructionFactory::get_instruction({340.0f, 360.0f}, 
                                                             current_dog_state.m_position));
   renderer.render(RenderInstructionFactory::get_instruction({340.0f + 25.0f, 360.0f + 25.0f}, 
                                                             {current_dog_state.m_position.x + 10.0f,
                                                              current_dog_state.m_position.y}));
   //////////////////////////////////////////////////////////////////////////////////////////////

   renderer.render_present();
}