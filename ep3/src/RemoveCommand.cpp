//Standard Libraries
#include <iostream>
#include <fstream>
#include <chrono>

//Interface
#include "RemoveCommand.hpp"
#include "FileSystem.hpp"

using namespace std;
using namespace std::chrono;

RemoveCommand::RemoveCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int RemoveCommand::execute(vector<string> args){
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  if(args.size() < 1){
    cout << "O comando rm precisa de um argumentos\n";
    return 1;
  }

  string fileName = args[0];

  auto targetFolder = fileSystem_->getPathFolder(fileName);
  
  if(targetFolder == NULL || fileName.size() == 0){
    cout << "Caminho inválido" << endl;
    return 0;
  }

  auto file = targetFolder->getFile(fileName);

  if(file == NULL){
    cout << "Este arquivo não existe." << endl;
    return 0;
  }

  if(file->isFolder()){
    cout << "Para remover diretorio use 'rmdir'" << endl;
    return 0; 
  }

  targetFolder->removeFile(fileName);

  fileSystem_->removeFile(file->getInitialBlock());
  fileSystem_->persist(targetFolder);

  return 1;
}
