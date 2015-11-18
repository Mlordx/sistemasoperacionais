// Main Library
#include "FileSystem.hpp"

// Standard Libraries
#include <iostream>

//EP3 Libraries
#include "Folder.hpp"


using namespace std;

void FileSystem::init(string fileName){
  if(isDisk(fileName)) return;
  disk_.close();
  disk_.open(fileName, ios::out);
  formatDisk();
  disk_.close();
  disk_.open(fileName, ios::in | ios::out);
  auto root  = shared_ptr<FileEntry>(new Folder("/"));
  persist(root, 0);
}

void FileSystem::formatDisk(){
  cout << BITMAP_POSITION << endl << TOTAL_SIZE << endl;
  char empty = 0;
  disk_.seekp(BITMAP_POSITION);
  for(int i = 0; i < FILE_BLOCKS/8+1; i++) disk_ << empty;
  disk_.seekp(TOTAL_SIZE);
  disk_ << "";
}

bool FileSystem::isDisk(string fileName){
  disk_.open(fileName, ios::in | ios::out);
  return disk_.good();
}

void FileSystem::persist(shared_ptr<FileEntry> entry, int block){
  char empty = 0;
  string text = entry->getData();
  string test;
  disk_.seekp(block*BLOCK_SIZE);
  disk_ << text;
  disk_ << empty;
  disk_ << flush;
}

void FileSystem::setCurrentFolder(shared_ptr<Folder> f){
  currentFolder_ = f;
}

shared_ptr<Folder> FileSystem::getCurrentFolder(){
  return currentFolder_;
}
  
