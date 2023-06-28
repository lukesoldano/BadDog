#pragma once
#include "Command.hpp"

class StopMoveLeft : public Command {

public:

   StopMoveLeft() = default;
   ~StopMoveLeft() = default;
   StopMoveLeft(const StopMoveLeft& sml) = default;
   StopMoveLeft(StopMoveLeft&&) = default;
   StopMoveLeft& operator=(StopMoveLeft&&) = default;

   void execute() override;

};