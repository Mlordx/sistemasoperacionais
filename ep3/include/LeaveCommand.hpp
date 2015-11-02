#ifndef HPP_LEAVECOMMAND_DEFINED
#define HPP_LEAVECOMMAND_DEFINED

//Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"

class LeaveCommand : public Command
{
 public:
  int execute(std::vector<std::string> args);
};

#endif