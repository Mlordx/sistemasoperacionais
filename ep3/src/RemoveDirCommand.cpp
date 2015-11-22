// Main Library
#include "RemoveDirCommand.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

RemoveDirCommand::RemoveDirCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int RemoveDirCommand::execute(std::vector<std::string> args){
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  shared_ptr<Folder> actualFolder;
  string folderName;

  if(args.size() < 1 || args[0] == "/"){
    cout << "Não é possível remover o diretório raíz" << endl;
    return 0;
  } 
  folderName = args[0];
  auto targetFolder = fileSystem_->getPathFolder(folderName);
  
  if(targetFolder == NULL || folderName.size() == 0){
    cout << "Caminho inválido" << endl;
    return 0;
  }
  
  actualFolder = targetFolder->getFolder(folderName);
  
  if(actualFolder == NULL){
    cout << "Não é um diretório" << endl;
    return 0;
  }

  actualFolder = fileSystem_->loadFolder(actualFolder->getInitialBlock());

  if(actualFolder == NULL){
    cout << "Este diretório não existe" << endl;
    return 0;
  }

  fileSystem_->removeFolder(actualFolder);
  targetFolder->removeFile(folderName);
  targetFolder->setModificationTime();
  fileSystem_->persist(targetFolder);

  return 0;
} 
