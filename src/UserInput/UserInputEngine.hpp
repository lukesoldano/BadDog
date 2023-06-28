#pragma once

namespace UserInput
{

// @warning This class is not thread safe
// @warning This class should not be sub-classed
class UserInputEngine
{
public:

   UserInputEngine() = default;
   ~UserInputEngine() = default;

   void initialize(){};
   void teardown() {};

   void process_input();

};

} // namespace UserInput