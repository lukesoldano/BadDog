#include "UserInputEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"

#include "SDL.h"

using namespace UserInput;

void UserInputEngine::process()
{
   auto& game_state = GameState::instance();

   // Reset inputs
   // game_state.m_key_pressed.fill(false);

   SDL_Event event;
   while (0 != SDL_PollEvent(&event) && !game_state.m_quit_program)
   {
      switch (event.type)
      {
         case SDL_QUIT:
            LOG_MESSAGE("USER QUIT");
            game_state.m_quit_program = true;
            break;
         case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
               case SDL_Scancode::SDL_SCANCODE_A:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::a)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_D:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::d)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_E:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::e)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_S:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::s)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_W:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::w)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_LSHIFT:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::lshift)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_LCTRL:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::lctrl)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_SPACE:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::space)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_RETURN:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::enter)] = true;
                  break;
               case SDL_Scancode::SDL_SCANCODE_ESCAPE:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::esc)] = true;
                  break;
               default:
                  LOG_MESSAGE("Unmapped key press, scan code: " << 
                              static_cast<int>(event.key.keysym.scancode));
                  break;
            }
            break;
         case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
               case SDL_Scancode::SDL_SCANCODE_A:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::a)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_D:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::d)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_E:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::e)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_S:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::s)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_W:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::w)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_LSHIFT:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::lshift)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_LCTRL:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::lctrl)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_SPACE:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::space)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_RETURN:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::enter)] = false;
                  break;
               case SDL_Scancode::SDL_SCANCODE_ESCAPE:
                  game_state.m_key_pressed[static_cast<uint8_t>(Key::esc)] = false;
                  break;
               default:
                  LOG_MESSAGE("Unmapped key release, scan code: " << 
                              static_cast<int>(event.key.keysym.scancode));
                  break;
            }
            break;
         default:
            break;
      }
   }
}