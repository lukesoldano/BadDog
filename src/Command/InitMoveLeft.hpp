#pragma once
#include "Command.hpp"

class InitMoveLeft : public Command {

public:

   InitMoveLeft() = default;
   ~InitMoveLeft() = default;
   InitMoveLeft(const InitMoveLeft& iml) = default;
   InitMoveLeft(InitMoveLeft&&) = default;
   InitMoveLeft& operator=(InitMoveLeft&&) = default;

   void execute() override;

};