// Main Library
#include "FileEntry.hpp"

//Standard Libraries
#include <iostream>
#include <cstdio>

using namespace std;

FileEntry::FileEntry(string name) : name_(name), size_(0){
  setCreationTime();
  setModificationTime();
  setAccessTime();
}

void FileEntry::initFromData(vector<string> filesInfo){
  setName(filesInfo[0]);
  setSize(atoi(filesInfo[1].c_str()));
  creationTime_ = atoi(filesInfo[2].c_str());
  modificationTime_ = atoi(filesInfo[3].c_str());
  accessTime_ = atoi(filesInfo[4].c_str());
  setInitialBlock(atoi(filesInfo[5].c_str()));
}

bool FileEntry::isFolder(){
  return false;
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

void FileEntry::setData(string data){
  size_ = data.size() + 1;
  data_ = data;
}

string FileEntry::getData(){
  return data_;
}

void FileEntry::printFormattedInfo(){

  struct tm * timeinfo;

  timeinfo = localtime(&modificationTime_);

  char date[11];
  strftime(date, 11, "%d/%m/%Y", timeinfo);

  printf("%-11s", date);
  printf("%-11d", size_);
  printf("%s\n", name_.c_str());
}
