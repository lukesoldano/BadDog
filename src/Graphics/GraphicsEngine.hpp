#pragma once

#include "IEngine.hpp"
#include "Window.hpp"

#include <memory>

namespace Graphics
{

class Engine final : public IEngine
{
   std::unique_ptr<Window> m_window;

public:

   Engine() = default;
   virtual ~Engine() = default;

   void initialize() override;
   void teardown() override;

   void process() override;

};

} // namespace Graphics