//Standard Libraries
#include <iostream>
#include <fstream>

//Interface
#include "CopyCommand.hpp"
#include "FileSystem.hpp"

using namespace std;

CopyCommand::CopyCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int CopyCommand::execute(vector<string> args){
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  if(args.size() < 2){
    cout << "O comando cp precisa de dois argumentos\n";
    return 1;
  }

  ifstream original(args[0]);
  stringstream buffer;
  buffer << original.rdbuf();
  string data = buffer.str();

  string newRelativeName = args[1];

  auto targetFolder = fileSystem_->getPathFolder(newRelativeName);
  
  if(targetFolder == NULL || newRelativeName.size() == 0){
    cout << "Caminho inválido" << endl;
    return 0;
  }

  if(targetFolder->getFile(newRelativeName) != NULL){
    cout << "Este nome já está sendo utilizado" << endl;
    return 0;
  }

  shared_ptr<FileEntry> newFile(new FileEntry(newRelativeName));
  newFile->setData(data);
  newFile->setInitialBlock(fileSystem_->getNextFreeBlock());
  targetFolder->addFile(newFile);
  
  fileSystem_->persist(targetFolder);
  targetFolder->setModificationTime();
  fileSystem_->persist(newFile);
  
  return 1;
}
