#pragma once

class ILogicEngine
{
public:

   ILogicEngine() = default;
   virtual ~ILogicEngine() = default;

   virtual void initialize() = 0;
   virtual void teardown() = 0;

   virtual void process() = 0;

};