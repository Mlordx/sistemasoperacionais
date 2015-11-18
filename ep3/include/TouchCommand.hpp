#ifndef HPP_TOUCHCOMMAND_DEFINED
#define HPP_TOUCHCOMMAND_DEFINED

// Standard Libraries
#include <string>
#include <vector>

// EP3 Classes
#include "Command.hpp"
#include "FileEntry.hpp"
#include "Folder.hpp"

class TouchCommand : public Command{
private:
  std::shared_ptr<Folder> currentFolder;
public:
  TouchCommand(std::shared_ptr<Folder> cf);
  int execute(std::vector<std::string> args);
};

#endif
