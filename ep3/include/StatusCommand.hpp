#ifndef HPP_STATUSCOMMAND_DEFINED
#define HPP_STATUSCOMMAND_DEFINED

//Standard Libraries
#include <string>
#include <vector>

//EP3 Classes
#include "Command.hpp"
#include "FileSystem.hpp"

class StatusCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  StatusCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif