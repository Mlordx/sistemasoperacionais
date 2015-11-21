#ifndef HPP_FINDCOMMAND_DEFINED
#define HPP_FINDCOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "FileSystem.hpp"

class FindCommand : public Command{
private:
  std::shared_ptr<FileSystem> fileSystem_;
public:
  FindCommand(std::shared_ptr<FileSystem> fs);
  int execute(std::vector<std::string> args);
};

#endif
