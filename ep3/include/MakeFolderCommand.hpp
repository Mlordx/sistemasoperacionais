#ifndef HPP_MAKEFOLDERCOMMAND_DEFINED
#define HPP_MAKEFOLDERCOMMAND_DEFINED

//Standard Libraries
#include <memory>
#include <vector>
#include <string>

//EP3 Libraries
#include "Command.hpp"
#include "FileSystem.hpp"

class MakeFolderCommand : public Command
{
 private:
  std::shared_ptr<FileSystem> fileSystem_;
 public:
  MakeFolderCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif