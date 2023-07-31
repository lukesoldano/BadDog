#pragma once

// #include "Camera.hpp"
#include "IEngine.hpp"
#include "Window.hpp"

// #include <memory>

namespace Graphics
{

class Engine : public IEngine
{
   std::unique_ptr<Window> m_window;

public:

   Engine() = default;
   virtual ~Engine() = default;

   void initialize();
   void teardown();

   void process();

};

} // namespace Graphics