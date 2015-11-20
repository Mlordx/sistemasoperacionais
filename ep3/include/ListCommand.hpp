#ifndef HPP_LISTCOMMAND_DEFINED
#define HPP_LISTCOMMAND_DEFINED

//Standard Libraries
#include <memory>
#include <vector>
#include <string>

//EP3 Libraries
#include "Command.hpp"
#include "FileSystem.hpp"

class ListCommand : public Command
{
 private:
  std::shared_ptr<FileSystem> fileSystem_;
 public:
  ListCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif