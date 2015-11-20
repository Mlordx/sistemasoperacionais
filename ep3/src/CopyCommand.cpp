//Standard Libraries
#include <iostream>
#include <fstream>

//Interface
#include "CopyCommand.hpp"
#include "FileSystem.hpp"

using namespace std;

CopyCommand::CopyCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int CopyCommand::execute(vector<string> args){
  if(args.size() < 2){
    cout << "O comando cp precisa de dois argumentos\n";
    return 1;
  }

  ifstream original(args[0]);
  stringstream buffer;
  buffer << original.rdbuf();
  string data = buffer.str();
  string newRelativeName = args[1];
  auto targetFolder = fileSystem_->getCurrentFolder(); //currentFolder_->getChildFolder(newRelativeName);
  shared_ptr<FileEntry> newFile(new FileEntry(newRelativeName));
  newFile->setData(data);
  targetFolder->addFile(newFile);
  fileSystem_->persist(newFile, fileSystem_->getNextFreeBlock());


  return 1;
}
  /*cout << "Copiando . . .\n";

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
// Libraries
#include "CopyCommand.hpp"*/