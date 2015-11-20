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

  string fileName = args[0];

  auto targetFolder = fileSystem_->getPathFolder(fileName);
  
  if(targetFolder == NULL || fileName.size() == 0){
    cout << "Caminho inválido" << endl;
    return 0;
  }
  
  cout << targetFolder->getData() << endl;
  auto targetFile = targetFolder->getFile(fileName);
  
  if(targetFile == NULL){
    cout << "Este arquivo não existe" << endl;
    return 0;
  }

  string data = fileSystem_->getFileData(targetFile->getInitialBlock());
  cout << data << endl;

  return 1;
}