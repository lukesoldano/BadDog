#pragma once

#include "EventTypes.hpp"
#include "IEngine.hpp"

#include <memory>
#include <vector>

namespace Game
{

class Engine
{
   std::vector<std::unique_ptr<IEngine>> m_sub_engines;

public:

   Engine(Engine&&) = default;
   virtual ~Engine() = default;

   inline static Engine& instance()
   {
      static Engine engine;
      return engine;
   }

   Engine& operator=(Engine&&) = default;

   bool initialize();
   bool teardown();

   void run_gameloop();

private:

   Engine() = default;
   Engine(const Engine&) = delete;
   Engine& operator=(const Engine&) = delete;

   void on_quit_requested(const Events::QuitProgramRequested& i_event);

};

} // namespace Game