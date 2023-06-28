#pragma once

#include "GraphicsEngine.hpp"
#include "ILogicEngine.hpp"
#include "UserInputEngine.hpp"

#include <memory>
#include <vector>

class Game
{
   std::unique_ptr<UserInput::UserInputEngine> m_user_input_engine;
   std::unique_ptr<Graphics::GraphicsEngine> m_graphics_engine;
   std::vector<std::unique_ptr<ILogicEngine>> m_logic_engines;

public:

   Game() = default;
   virtual ~Game() = default;

   int initialize();
   void teardown();

   void run_gameloop();

};