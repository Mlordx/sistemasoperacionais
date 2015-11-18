//Standard Libraries
#include <iostream>

// Interface
#include "TouchCommand.hpp"

using namespace std;

TouchCommand::TouchCommand(shared_ptr<Folder> cf) : currentFolder(cf) {}


int TouchCommand::execute(vector<string> args){
  cout << "Toquei . . . \n";
  for(auto files : currentFolder->getFiles()){
    if(files->getName() == args[0]){
      files->setModificationTime();
      return 1;
    }
  }
  shared_ptr<FileEntry> newFile(new FileEntry(args[0]));
  currentFolder->addFile(newFile);
  return 1;
}
