#ifndef HPP_REMOVECOMMAND_DEFINED
#define HPP_REMOVECOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "Folder.hpp"
#include "FileSystem.hpp"

class RemoveCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  RemoveCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif