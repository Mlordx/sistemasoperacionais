// Main Library
#include "PrintCommand.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

PrintCommand::PrintCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int PrintCommand::execute(std::vector<std::string> args){
  if(args.size() < 1){
    cout << "O comando cat precisa de um argumento\n";
    return 1;
  }

  auto targetFolder = fileSystem_->getCurrentFolder(); //currentFolder_->getChildFolder(newRelativeName);
  auto targetFile = targetFolder->getFile(args[0]);
  string data = fileSystem_->getFileData(targetFile->getInitialBlock());
  cout << data << endl;

  return 1;
}