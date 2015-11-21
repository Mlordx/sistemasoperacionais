// Interface
#include "StatusCommand.hpp"

//Standard Libraries
#include <iostream>

//EP3 Libraries
#include "FileSystem.hpp"

using namespace std;

int StatusCommand::execute(vector<string> args){
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  fileSystem_->printInfo();
  return 1;
}


StatusCommand::StatusCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}