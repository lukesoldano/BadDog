#pragma once
#include "Command.hpp"

class InitMoveRight : public Command {

public:

   InitMoveRight() = default;
   ~InitMoveRight() = default;
   InitMoveRight(const InitMoveRight& imr) = default;
   InitMoveRight(InitMoveRight&&) = default;
   InitMoveRight& operator=(InitMoveRight&&) = default;

   void execute() override;

};