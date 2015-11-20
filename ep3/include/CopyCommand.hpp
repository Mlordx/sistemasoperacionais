#ifndef HPP_COPYCOMMAND_DEFINED
#define HPP_COPYCOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "Folder.hpp"
#include "FileSystem.hpp"

class CopyCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  CopyCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif