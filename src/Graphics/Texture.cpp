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
   m_texture(other.m_texture),
   m_width(other.m_width),
   m_height(other.m_height)
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
      this->m_width = rhs.m_width;
      this->m_height = rhs.m_height;
      rhs.m_texture = nullptr;
      rhs.m_width = 0;
      rhs.m_height = 0;
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

int Texture::get_width() const 
{ 
   return m_width; 
}

int Texture::get_height() const 
{ 
   return m_height; 
}
