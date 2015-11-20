// Main Library
#include "ListCommand.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

ListCommand::ListCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int ListCommand::execute(std::vector<std::string> args){

  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  shared_ptr<Folder> actualFolder;
  string folderName;

  if(args.size() < 1 || args[0] == "/"){
    folderName = "/";
    actualFolder = fileSystem_->getCurrentFolder();
  } 
  else {
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
  }

  if(actualFolder == NULL){
    cout << "Este diretório não existe" << endl;
    return 0;
  }

  auto files = actualFolder->getFiles();
  unsigned int i = (folderName == "/" ? 0 : 1);
  printf("DATE       SIZE       NAME\n");
  printf("----------------------------------------------\n");
  for (; i < files.size(); i++)
    files[i]->printFormattedInfo();
  return 1;

}
