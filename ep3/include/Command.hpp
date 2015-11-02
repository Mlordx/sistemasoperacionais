#ifndef HPP_COMMAND_DEFINED
#define HPP_COMMAND_DEFINED

//Standard Libraries
#include <string>
#include <vector>

class Command
{
 public:
  virtual int execute(std::vector<std::string> args) =0;
};

#endif