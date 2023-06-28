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
   std::unordered_map<EntityId_t, SDL_FRect> m_active_entities = { {0, {0.0, 0.0, 20.0, 20.0}} };
   std::unordered_map<EntityId_t, SDL_FRect> m_static_entities = { 
                                                                    {1, {300.0, 100.0, 70.0, 70.0}},
                                                                    {2, {200.0, 370.0, 50.0, 75.0}},
                                                                    {3, {400.0, 400.0, 50.0, 25.0}},
                                                                    {4, {550.0, 400.0, 50.0, 55.0}}
                                                                 };
   //

private:

   GameState() = default; 
   ~GameState() = default;

};