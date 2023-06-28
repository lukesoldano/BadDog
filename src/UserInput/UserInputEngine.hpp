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

   // @warning Throws on failure
   void initialize();

   // @note A symmetrical call to teardown should be made if a call to initialize was made
   void teardown();

   void process();

};

} // namespace Graphics