// Main Library
#include "FileSystem.hpp"

// Standard Libraries
#include <iostream>


using namespace std;

void FileSystem::init(string fileName){
  cout << fileName << endl;
  disk_.open(fileName, ios::in);
  if(disk_.good())
    return;
  disk_.close();
  disk_.open(fileName, ios::out);
  formatDisk();
}

void FileSystem::formatDisk(){
  cout << BITMAP_POSITION << endl << TOTAL_SIZE << endl;
  char empty = 37;
  //disk_
  disk_.seekp(BITMAP_POSITION);
  for(int i = 0; i < FILE_BLOCKS/8+1; i++)
    disk_ << empty;
  disk_.seekp(TOTAL_SIZE);
  disk_ << "Z";
  disk_ << flush;
}