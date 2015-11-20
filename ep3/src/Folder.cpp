// Main Library
#include "Folder.hpp"

// Standard Libraries
#include <iostream>

using namespace std;

Folder::Folder(string name) : FileEntry(name){
}

Folder::Folder(string name, shared_ptr<FileEntry> parent) : FileEntry(name){

  addParent(parent);
}

bool Folder::isFolder(){
  return true;
}

void Folder::addFile(shared_ptr<FileEntry> file){
  files_.push_back(file);
}

void Folder::addParent(shared_ptr<FileEntry> parent){
  addFile(parent);
}

string Folder::getData(){
  string data;
  data = generateData();
  for(auto entry : files_)
    data+= "\n" + generateData(entry);
  return data;
}

string Folder::generateData(){
  string data = getName() + ';';
  data += to_string(getSize()) + ';';
  data += to_string(getCreationTime()) + ';';
  data += to_string(getModificationTime()) + ';';
  data += to_string(getAccessTime()) + ';';
  data += to_string(getInitialBlock()) + ';';
  return data;
}

string Folder::generateData(std::shared_ptr<FileEntry> entry){
  string data = entry->getName() + ';';
  data += to_string(entry->getSize()) + ';';
  data += to_string(entry->getCreationTime()) + ';';
  data += to_string(entry->getModificationTime()) + ';';
  data += to_string(entry->getAccessTime()) + ';';
  data += to_string(entry->getInitialBlock()) + ';';
  return data;
}

vector<shared_ptr<FileEntry> >& Folder::getFiles(){
  return files_;
}

shared_ptr<Folder> Folder::getChildFolder(string completeName){
  cout << "olá\n";
  return NULL;
}

shared_ptr<FileEntry> Folder::getFile(string fileName){
  for(auto file : files_){
    if(file->getName() == fileName){
      cout << "saiu" << endl;
      return file;
    }
  }
  return NULL;
}