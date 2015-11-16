// Main Library
#include "FileEntry.hpp"

//Standard Libraries
#include <iostream>

using namespace std;

FileEntry::FileEntry(string name) : name_(name), size_(0){

  setCreationTime();
  setModificationTime();
  setAccessTime();
}

string FileEntry::getName(){

  return name_;
}

int FileEntry::getSize(){

  return size_;
}

time_t FileEntry::getCreationTime(){

  return creationTime_;
}

time_t FileEntry::getModificationTime(){

  return modificationTime_;
}

time_t FileEntry::getAccessTime(){

  return accessTime_;
}

void FileEntry::setName(string name){

  name_ = name;
}

void FileEntry::setSize(int size){

  size_ = size;
}

void FileEntry::setCreationTime(){

  time (&creationTime_);
}

void FileEntry::setModificationTime(){

  time (&modificationTime_);
}

void FileEntry::setAccessTime(){

  time (&accessTime_);
}

int FileEntry::getInitialBlock(){

  return initialBlock_;
}
void FileEntry::setInitialBlock(int initialBlock){

  initialBlock_ = initialBlock;
}

string FileEntry::getData(){
  return "oi";
}