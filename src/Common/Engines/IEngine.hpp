#pragma once

class IEngine
{
public:

   IEngine() = default;
   virtual ~IEngine() = default;

   virtual void initialize() = 0;
   virtual void teardown() = 0;

   virtual void process() = 0;

};