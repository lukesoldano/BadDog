#pragma once

#include "ProjectDefs.hpp"
#include "UserInputDefs.hpp"

#include "SDL_rect.h"

#include <array>
#include <unordered_map>

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
   std::unordered_map<EntityId_t, SDL_Rect> m_active_entities = { {0, {0, 0, 20, 20}} };
   std::unordered_map<EntityId_t, SDL_Rect> m_static_entities = { {1, {300, 200, 50, 50}} };
   //

private:

   GameState() = default; 
   ~GameState() = default;

};