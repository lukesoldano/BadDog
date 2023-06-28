#pragma once
#include "Command.hpp"

class StopMoveRight : public Command {

public:

   StopMoveRight() = default;
   ~StopMoveRight() = default;
   StopMoveRight(const StopMoveRight& smr) = default;
   StopMoveRight(StopMoveRight&&) = default;
   StopMoveRight& operator=(StopMoveRight&&) = default;

   void execute() override;

};