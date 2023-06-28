#include "Surface.hpp"

#include "Logger.hpp"
#include "ProjectDefs.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <assert.h>

using namespace Graphics;

Surface::Surface(SDL_Surface* i_sdl_surface) :
   m_sdl_surface(i_sdl_surface)
{
   CHECK_IF_POINTER_VALID(i_sdl_surface);
}

Surface::Surface(Surface&& other) :
   m_sdl_surface(other.m_sdl_surface)
{
   other.m_sdl_surface = nullptr;
}

Surface::~Surface()
{
   teardown_internal();
}

Surface& Surface::operator=(Surface&& rhs)
{
   if (this != &rhs)
   {
      this->m_sdl_surface = rhs.m_sdl_surface;
      rhs.m_sdl_surface = nullptr;
   }

   return *this;
}

std::optional<Surface> Surface::create_from_image(FileSystem::Path i_image_path)
{
	auto surface = IMG_Load(i_image_path.m_path.c_str());
	if (nullptr == surface)
	{
      LOG_ERROR("Failed to create an SDL surface using path: " << 
                i_image_path.m_path << 
                " - IMG error: " << 
                IMG_GetError());
      return std::nullopt;
	}

   return std::optional<Surface>({surface});
}

void Surface::teardown()
{
   teardown_internal();
}

void Surface::teardown_internal()
{
   if (nullptr != m_sdl_surface)
   {
      SDL_FreeSurface(m_sdl_surface);
      m_sdl_surface = nullptr;
   }
}

// @TODO I hate exposing this type directly, refactor this later - should only see this being
//       used in the Renderer class when creating textures
SDL_Surface* Surface::get_sdl_surface() const
{
   return m_sdl_surface;
}

