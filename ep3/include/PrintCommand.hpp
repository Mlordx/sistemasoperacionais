#ifndef HPP_PRINTCOMMAND_DEFINED
#define HPP_PRINTCOMMAND_DEFINED

//Standard Library
#include <memory>
#include <string>
#include <vector>

//EP3 Libraries
#include "FileSystem.hpp"
#include "Command.hpp"

class PrintCommand : public Command
{
 private:
  std::shared_ptr<FileSystem> fileSystem_;
 public:
  PrintCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif
