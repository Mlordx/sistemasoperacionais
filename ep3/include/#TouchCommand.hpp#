#ifndef HPP_TOUCHCOMMAND_DEFINED
#define HPP_TOUCHCOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "FileSystem.hpp"

class TouchCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  TouchCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif
