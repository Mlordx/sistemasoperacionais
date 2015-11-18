//Standard Libraries
#include <iostream>

//Interface
#include "CopyCommand.hpp"

using namespace std;

CopyCommand::CopyCommand(shared_ptr<Folder> cf) : currentFolder(cf) {}

int CopyCommand::execute(vector<string> args){
  cout << "Copiando . . .\n";

  for(auto files : currentFolder->getFiles()){
    if(files->getName() == args[0]){
      auto size = files->getSize();
      auto iniBlock = files->getInitialBlock();
      auto newFile = make_shared<FileEntry>(args[1]);
      newFile->setSize(size);
      newFile->setInitialBlock(iniBlock);
      currentFolder->addFile(newFile);
    }
  }
  return 1;
}
