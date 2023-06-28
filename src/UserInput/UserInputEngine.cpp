#include "UserInputEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"

#include "SDL.h"

using namespace UserInput;

void UserInputEngine::initialize()
{
   // do nothing
}

void UserInputEngine::teardown()
{
   // do nothing
}

void UserInputEngine::process()
{
   SDL_Event event;
   while (0 != SDL_PollEvent(&event) && !GameState::Instance().m_quit_program)
   {
      switch (event.type)
      {
         case SDL_QUIT:
            LOG_MESSAGE("USER QUIT");
            GameState::Instance().m_quit_program = true;
            break;
         case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
               case SDL_Scancode::SDL_SCANCODE_A:
                  LOG_MESSAGE("KEY DOWN A");
                  break;
               case SDL_Scancode::SDL_SCANCODE_D:
                  LOG_MESSAGE("KEY DOWN D");
                  break;
               case SDL_Scancode::SDL_SCANCODE_S:
                  LOG_MESSAGE("KEY DOWN S");
                  break;
               case SDL_Scancode::SDL_SCANCODE_W:
                  LOG_MESSAGE("KEY DOWN W");
                  break;
               default:
                  LOG_MESSAGE("KEY DOWN ___");
                  break;
            }
            break;
         case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
               case SDL_Scancode::SDL_SCANCODE_A:
                  LOG_MESSAGE("KEY UP A");
                  break;
               case SDL_Scancode::SDL_SCANCODE_D:
                  LOG_MESSAGE("KEY UP D");
                  break;
               case SDL_Scancode::SDL_SCANCODE_S:
                  LOG_MESSAGE("KEY UP S");
                  break;
               case SDL_Scancode::SDL_SCANCODE_W:
                  LOG_MESSAGE("KEY UP W");
                  break;
               default:
                  LOG_MESSAGE("KEY UP ___");
                  break;
            }
            break;
         default:
            break;
      }
   }
}