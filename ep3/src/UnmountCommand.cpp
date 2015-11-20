// Interface
#include "UnmountCommand.hpp"

//Standard Libraries
#include <iostream>

//EP3 Libraries
#include "FileSystem.hpp"

using namespace std;

int UnmountCommand::execute(vector<string> args){
  cout << "Desmontando sistema de arquivos...\n";
  
  if(!fileSystem_->isOpen()){
    cout << "Sistema já está desmontado" << endl;
    return 0;
  }

  fileSystem_->close();
  return 1;
}


UnmountCommand::UnmountCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}