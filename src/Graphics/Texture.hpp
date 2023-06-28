#pragma once

// Forward declarations
class SDL_Texture;

namespace Graphics
{

// @warning This class is not thread safe 
class Texture
{
   // Friend permissions provided as the Renderer acts as a factory for Textures
   friend class Renderer;

   SDL_Texture* m_texture = nullptr;
   int m_width = 0;
   int m_height = 0;

public:

   Texture() = delete;
   Texture(const Texture&) = delete;
   Texture(Texture&&);

   virtual ~Texture();

   Texture& operator=(const Texture&) = delete;
   Texture& operator=(Texture&&);

   // @warning Teardown any Texture before exiting the SDL for the sake of cleanliness
   void teardown();

   // @TODO REMOVE, just messin' around
   SDL_Texture* get_sdl_texture() const { return m_texture; }

   int get_width() const;
   int get_height() const;

private:

   // @TODO Move definition to source
   Texture(SDL_Texture* i_texture, const int i_width, const int i_height) :
      m_texture(i_texture),
      m_width(i_width),
      m_height(i_height)
   {
      //CHECK_IF_POINTER_VALID(i_texture);
   }

   void teardown_internal();

};

} // Graphics