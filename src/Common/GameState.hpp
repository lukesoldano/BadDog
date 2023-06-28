#pragma once

#include "UserInputDefs.hpp"

#include <array>
#include "SDL_rect.h"

class GameState
{
public:

   static GameState& instance()
   {
      static GameState game_state;
      return game_state;
   }

   // Meta state parameters
   bool m_quit_program = false;

   // User input state parameters, index associated with key enum value
   std::array<bool, static_cast<size_t>(Key::MAX_VALUE)> m_key_pressed{ false };

   // TODO REMOVE - HERE FOR TESTING
   
   SDL_Rect m_player_position = {0, 0, 20, 20};
   SDL_Rect m_obstacle_position = {300, 200, 80, 200};
   //

private:

   GameState() = default; 
   ~GameState() = default;

};