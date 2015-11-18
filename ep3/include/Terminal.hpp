#ifndef HPP_TERMINAL_DEFINED
#define HPP_TERMINAL_DEFINED

//Standard Libraries
#include <map>
#include <string>
#include <memory>

//EP3 Classes
#include "Command.hpp"
#include "FileSystem.hpp"

using command_map = std::map<std::string, std::shared_ptr<Command> >;

class Terminal{
 private:
  std::shared_ptr<FileSystem> fileSystem_;
  command_map commands_;
 public:
  Terminal();
  void run(char*);
};

#endif
