//Standard Libraries
#include <iostream>

// Interface
#include "TouchCommand.hpp"

using namespace std;

TouchCommand::TouchCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}


int TouchCommand::execute(vector<string> args){
  auto currentFolder = fileSystem_->getCurrentFolder();
  cout << "Toquei . . . \n";
  for(auto files : currentFolder->getFiles()){
    if(files->getName() == args[0]){
      files->setModificationTime();
      fileSystem_->persist(files);
      return 1;
    }
  }
  shared_ptr<FileEntry> newFile(new FileEntry(args[0]));
  newFile->setInitialBlock(fileSystem_->getNextFreeBlock());
  currentFolder->addFile(newFile);

  fileSystem_->persist(currentFolder);
  fileSystem_->persist(newFile);
  
  return 1;
}
