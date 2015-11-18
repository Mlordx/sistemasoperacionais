#ifndef HPP_COPYCOMMAND_DEFINED
#define HPP_COPYCOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "Folder.hpp"

class CopyCommand : public Command{
private:
  std::shared_ptr<Folder> currentFolder;
public:
  CopyCommand(std::shared_ptr<Folder> cf);
  int execute(std::vector<std::string> args);
};

#endif
