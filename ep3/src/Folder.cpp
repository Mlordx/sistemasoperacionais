// Main Library
#include "Folder.hpp"

// Standard Libraries
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string>& split(const string &input, char delim, vector<string> &args) {
  stringstream stream(input);
  string item;
  
  while (getline(stream, item, delim)) 
    if(item != "") args.push_back(item);
  
  return args;
}

Folder::Folder(string name) : FileEntry(name){
}

Folder::Folder(string name, shared_ptr<FileEntry> parent) : FileEntry(name){

  addParent(parent);
}

Folder::Folder(string name, string data) : FileEntry(name){
  
  vector<string> filesData;
  vector<string> filesInfo;
  split(data, '\n', filesData);

  split(filesData[0], ';', filesInfo);
  initFromData(filesInfo);
  filesData.erase(filesData.begin());

  for(auto fileData : filesData){
    addFile(createEntry(fileData));
  }
}

shared_ptr<FileEntry> Folder::createEntry(string data){
  vector<string> filesInfo;
  split(data, ';', filesInfo);
  if(filesInfo[6] == "1"){
    shared_ptr<Folder> folder(new Folder(""));
    folder->initFromData(filesInfo);
    return folder;
  }
  shared_ptr<FileEntry> fileEntry(new FileEntry(""));
  fileEntry->initFromData(filesInfo);
  return fileEntry;
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
  data += to_string(isFolder()) + ';';
  return data;
}

string Folder::generateData(std::shared_ptr<FileEntry> entry){
  string data = entry->getName() + ';';
  data += to_string(entry->getSize()) + ';';
  data += to_string(entry->getCreationTime()) + ';';
  data += to_string(entry->getModificationTime()) + ';';
  data += to_string(entry->getAccessTime()) + ';';
  data += to_string(entry->getInitialBlock()) + ';';
  data += to_string(entry->isFolder()) + ';';
  return data;
}

vector<shared_ptr<FileEntry> >& Folder::getFiles(){
  return files_;
}

shared_ptr<FileEntry> Folder::getFile(string fileName){
  for(auto file : files_){
    if(file->getName() == fileName){
      return file;
    }
  }
  return NULL;
}

shared_ptr<Folder> Folder::getFolder(string folderName){
  for(auto file : files_){
    if(file->getName() == folderName && file->isFolder()){
      shared_ptr<Folder> folder;
      folder = std::static_pointer_cast<Folder>(file);
      return folder;
    }
  }
  return NULL;
}