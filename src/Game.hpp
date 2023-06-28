#pragma once

#include "IEngine.hpp"

#include <memory>
#include <vector>

class Game
{
   std::vector<std::unique_ptr<IEngine>> m_engines;

public:

   Game() = default;
   virtual ~Game() = default;

   int initialize();
   void teardown();

   void run_gameloop();

};