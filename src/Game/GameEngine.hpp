#pragma once

#include "IEngine.hpp"

#include <memory>
#include <vector>

namespace Game
{

class Engine
{
   std::vector<std::unique_ptr<IEngine>> m_sub_engines;

public:

   Engine() = default;
   virtual ~Engine() = default;

   int initialize();
   void teardown();

   void run_gameloop();

};

} // namespace Game