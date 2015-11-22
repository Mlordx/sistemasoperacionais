// Main Library
#include "MakeFolderCommand.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

MakeFolderCommand::MakeFolderCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int MakeFolderCommand::execute(std::vector<std::string> args){
  
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  if(args.size() < 1){
    cout << "O comando mkdir precisa de um argumento\n";
    return 1;
  }

  string folderName = args[0];
  auto targetFolder = fileSystem_->getPathFolder(folderName);
  if(targetFolder == NULL || folderName.size() == 0){
    cout << "Caminho inválido" << endl;
    return 0;
  }

  if(targetFolder->getFile(folderName) != NULL){
    cout << "Este nome já está sendo utilizado" << endl;
    return 0;
  }

  shared_ptr<Folder> folder(new Folder(folderName, targetFolder));
  folder->setInitialBlock(fileSystem_->getNextFreeBlock());
  fileSystem_->persist(folder);

  targetFolder->addFile(folder);
  targetFolder->setModificationTime();
  fileSystem_->persist(targetFolder);

  return 1;
}