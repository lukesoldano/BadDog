#include "Texture.hpp"

// #include "Logger.hpp"
// #include "ProjectDefs.hpp"

#include "SDL_render.h"

using namespace Graphics;

// @TODO Move definition back to source
// Texture::Texture(SDL_Texture* i_texture) :
//    m_texture(i_texture)
// {
//    CHECK_IF_POINTER_VALID(i_texture);
// }

Texture::Texture(Texture&& other) :
   m_texture(other.m_texture)
{
   other.m_texture = nullptr;
}

Texture::~Texture()
{
   teardown_internal();
}

Texture& Texture::operator=(Texture&& rhs)
{
   if (this != &rhs)
   {
      this->m_texture = rhs.m_texture;
      rhs.m_texture = nullptr;
   }

   return *this;
}

void Texture::teardown()
{
   teardown_internal();
}

void Texture::teardown_internal()
{
   if (nullptr != m_texture)
   {
      SDL_DestroyTexture(m_texture);
      m_texture = nullptr;
   }
}
