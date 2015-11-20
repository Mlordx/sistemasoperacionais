//Standard Libraries
#include <iostream>

//EP3 Libraries
#include "FileSystem.hpp"

//Interface
#include "MountCommand.hpp"

using namespace std;

int MountCommand::execute(vector<string> args){
  string fileName = args[0];
  cout << "Carregando sistema de arquivos...\n";
  
  if(fileSystem_->isOpen()){
    cout << "Sistema já montado, use 'unmount' antes de montar um novo" << endl;
    return 0;
  }

  fileSystem_->init(fileName);
  return 1;
}


MountCommand::MountCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}
