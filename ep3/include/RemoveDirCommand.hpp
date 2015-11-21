#ifndef HPP_REMOVEDIRCOMMAND_DEFINED
#define HPP_REMOVEDIRCOMMAND_DEFINED

//Standard Libraries
#include <memory>
#include <vector>
#include <string>

//EP3 Libraries
#include "Command.hpp"
#include "FileSystem.hpp"

class RemoveDirCommand : public Command
{
 private:
  std::shared_ptr<FileSystem> fileSystem_;
 public:
  RemoveDirCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif