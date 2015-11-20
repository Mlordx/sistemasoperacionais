#ifndef HPP_UNMOUNTCOMMAND_DEFINED
#define HPP_UNMOUNTCOMMAND_DEFINED

//Standard Libraries
#include <string>
#include <vector>

//EP3 Classes
#include "Command.hpp"
#include "FileSystem.hpp"

class UnmountCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  UnmountCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif