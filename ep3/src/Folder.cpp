// Main Library
#include "Folder.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

Folder::Folder(string name) : FileEntry(name){
  
  cout << "sem pai" << endl;
  
  for(auto file : files_){
    cout << file->getName() << endl;
  }
}

Folder::Folder(string name, shared_ptr<FileEntry> parent) : FileEntry(name){

  cout << "com pai" << endl;
  
  addParent(parent);
  for(auto file : files_){
    cout << file->getName() << endl;
  }
}

void Folder::addFile(shared_ptr<FileEntry> file){
  files_.push_back(file);
}

void Folder::addParent(shared_ptr<FileEntry> parent){
  addFile(parent);
}

string Folder::getData(){
  string data;
  data += getName() + ';';
  data += to_string(getSize()) + ';';
  data += to_string(getCreationTime()) + ';';
  data += to_string(getModificationTime()) + ';';
  data += to_string(getAccessTime()) + ';';
  data += to_string(getInitialBlock()) + ';';
  cout << data << endl;
  return data;
}