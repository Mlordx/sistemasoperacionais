#ifndef HPP_MOUNTCOMMAND_DEFINED
#define HPP_MOUNTCOMMAND_DEFINED

//Standard Libraries
#include <string>
#include <vector>

//EP3 Classes
#include "Command.hpp"
#include "FileSystem.hpp"

class MountCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  MountCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif
