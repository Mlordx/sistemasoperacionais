#ifndef HPP_TERMINAL_DEFINED
#define HPP_TERMINAL_DEFINED

//Standard Libraries
#include <map>
#include <string>
#include <memory>

//EP3 Classes
#include "Command.hpp"

using command_map = std::map<std::string, std::shared_ptr<Command>>;

class Terminal
{
 private:
  command_map commands_;
 public:
  Terminal();
  void run(char*);
};

#endif