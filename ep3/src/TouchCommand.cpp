//Standard Libraries
#include <iostream>
#include <algorithm>


// Interface
#include "TouchCommand.hpp"

using namespace std;

TouchCommand::TouchCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}


int TouchCommand::execute(vector<string> args){
  auto currentFolder = fileSystem_->getPathFolder(args[0]);
  string fileName;
  vector<char> name;
  auto fullPath = args[0];
  int i = fullPath.length()-1;
  char c = fullPath[i];
  while( c != '/'){
    name.push_back(fullPath[c]);
    c = fullPath[--i];
  }

  reverse(name.begin(),name.end());
for(int i = 0; i < (int)name.size(); i++) fileName+=name[i];
  
  cout << "Toquei . . . \n";
  for(auto files : currentFolder->getFiles()){
    if(files->getName() == args[0]){
      files->setModificationTime();
      fileSystem_->persist(files);
      return 1;
    }
  }
  shared_ptr<FileEntry> newFile(new FileEntry(args[0]));
  newFile->setInitialBlock(fileSystem_->getNextFreeBlock());
  currentFolder->addFile(newFile);

  fileSystem_->persist(currentFolder);
  currentFolder->setModificationTime();
  fileSystem_->persist(newFile);
  
  return 1;
}
