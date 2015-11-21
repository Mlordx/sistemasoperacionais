// Standard Libraries
#include <iostream>
#include <queue>
#include <utility>

// Interface
#include "FindCommand.hpp"

using namespace std;

FindCommand::FindCommand(shared_ptr<FileSystem> fs) : fileSystem_(fs) {}

int FindCommand::execute(vector<string> args){
  if(args.size() < 2 ){
    cout << "Número de argumentos insuficiente!\n";
    return 0;
  }

  
  if(!fileSystem_->isOpen()){
    cout << "Sistema ainda não está montado, use 'mount FILE'" << endl;
    return 0;
  }

  shared_ptr<Folder> actualFolder;
  string folderName;

  if(args[0] == "/"){
    folderName = "/";
    actualFolder = fileSystem_->getCurrentFolder();
  } 
  else{
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
  

  queue<pair<int,string> > folders;
  folders.push(make_pair(actualFolder->getInitialBlock(),""));

  while(!folders.empty()){
    auto top = folders.front();
    auto iniBlock = top.first;
    folders.pop();
    auto folder = fileSystem_->loadFolder(iniBlock);
    string path;
    if(folder->getName() != "/")  path = top.second + folder->getName() + "/";
    else path = "/";

    int i = 0;
    for(auto files : folder->getFiles()){
      if((i != 0) && files->isFolder()){
	folders.push(make_pair(files->getInitialBlock(),path));
      }
      if(files->getName() == args[1]){
	if(files->isFolder()){
	  cout << path + files->getName() +"/" << endl;
	}else cout << path + files->getName() << endl;
      }
      i++;
    }
  }
  return 1;
}
