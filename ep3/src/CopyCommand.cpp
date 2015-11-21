//Standard Libraries
#include <iostream>
#include <fstream>
#include <chrono>

//Interface
#include "CopyCommand.hpp"
#include "FileSystem.hpp"

using namespace std;
using namespace std::chrono;

CopyCommand::CopyCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int CopyCommand::execute(vector<string> args){
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
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
  fileSystem_->persist(newFile);
  
  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  auto duration = duration_cast<microseconds>( t2 - t1 ).count();
  cout << "Tempo: " << duration << endl;
  return 1;
}
