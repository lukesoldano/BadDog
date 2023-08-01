#pragma once

#include "IEngine.hpp"

namespace UserInput
{

class Engine final : public IEngine
{
public:

   Engine() = default;
   virtual ~Engine() = default;

   void initialize() override {}
   void teardown() override {}

   void process() override;

};

} // namespace UserInput