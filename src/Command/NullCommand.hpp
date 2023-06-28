#pragma once
#include "Command.hpp"
class NullCommand : public Command {

public:

   NullCommand() = default;
   ~NullCommand() = default;
   NullCommand(const NullCommand& n) = default;
   NullCommand(NullCommand&&) = default;
   NullCommand& operator=(NullCommand&&) = default;

   void execute() override;

};