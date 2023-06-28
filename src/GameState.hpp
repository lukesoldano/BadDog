#pragma once

class GameState
{
public:

   static GameState& Instance()
   {
      static GameState game_state;
      return game_state;
   }

   bool m_quit_program = false;

private:

   GameState() = default; 
   ~GameState() = default;

};