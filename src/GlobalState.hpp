#pragma once

#include "Logger.hpp"
#include "Texture.hpp"

#include "SDL_rect.h"

#include <memory>

class GlobalState
{
public:

   struct DogState
   {
      double m_theta = 0.0f;
      SDL_FPoint m_position;
   };

   static GlobalState& Instance()
   {
      static auto instance = GlobalState();
      return instance;
   }

   // Loaded textures
   std::unique_ptr<Graphics::Texture> m_background_texture;

   // Game object states
   DogState m_last_dog_state;
   DogState m_current_dog_state;

private:

   GlobalState() = default;

};
