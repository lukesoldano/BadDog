#pragma once

#include "IEngine.hpp"

namespace UserInput
{

// @warning This class is not thread safe
// @warning This class should not be sub-classed
class UserInputEngine : public IEngine
{
public:

   UserInputEngine() = default;
   virtual ~UserInputEngine() = default;

   void initialize() override final {};
   void teardown() override final {};

   void process() override final;

};

} // namespace UserInput