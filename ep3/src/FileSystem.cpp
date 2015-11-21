// Main Library
#include "FileSystem.hpp"

// Standard Libraries
#include <iostream>
#include <string.h>
#include <iomanip>

//EP3 Libraries
#include "Folder.hpp"


using namespace std;

char* cleanIndex(string index, char* filtered);

void FileSystem::init(string fileName){

  cout << "N_BLOCKS = " << N_BLOCKS << endl;
  cout << "BLOCK_SIZE = " << BLOCK_SIZE << endl;
  cout << "TOTAL_SIZE = " << TOTAL_SIZE << endl;
  cout << "BITMAP_POSITION = " << BITMAP_POSITION << endl;
  cout << "FILEMAP_POSITION = " << FILEMAP_POSITION << endl;

  if(isDisk(fileName)) {
    initFileMap();
    setCurrentFolder(loadFolder(0));
    return;
  }
  disk_.close();
  disk_.open(fileName, ios::out);
  formatDisk();
  disk_.close();
  disk_.open(fileName, ios::in | ios::out);
  auto root  = shared_ptr<Folder>(new Folder("/"));
  if(!disk_.good())
    cout << "Já Morreu!\n";
  initFileMap();
  root->setInitialBlock(getNextFreeBlock());
  persist(root);
  setCurrentFolder(root);
}

void FileSystem::formatDisk(){
  char empty = 0;
  disk_.seekp(BITMAP_POSITION);
  for(int i = 0; i < FILE_BLOCKS/8+1; i++) disk_ << empty;
  disk_.seekp(TOTAL_SIZE-1);
  disk_ << "";
}

bool FileSystem::isDisk(string fileName){
  disk_.open(fileName, ios::in | ios::out);
  return disk_.good();
}

bool FileSystem::isOpen(){
  return disk_.is_open();
}

void FileSystem::persist(shared_ptr<FileEntry> entry){
  int block = entry->getInitialBlock();
  auto blocks = getFileChunks(entry->getData());
  int newBlock;
  for (auto text : blocks){
    disk_.seekp(block*BLOCK_SIZE);
    disk_ << text;
    if(text.size() < BLOCK_SIZE - 1)
      newBlock = 0;
    else
      newBlock = getNextFreeBlock();
    addMapRegistry(block, newBlock);
    block = newBlock;
  }
  disk_ << flush;
}

void FileSystem::setCurrentFolder(shared_ptr<Folder> f){
  currentFolder_ = f;
}

shared_ptr<Folder> FileSystem::getCurrentFolder(){
  return currentFolder_;
}

shared_ptr<Folder> FileSystem::loadFolder(int block){
  string data = getFileData(block);
  shared_ptr<Folder> folder(new Folder("", data));
  return folder;
}

shared_ptr<Folder> FileSystem::getInitialFolder(string& path){
  if (path[0] != '/'){
    return currentFolder_;
  }
  path.erase(0, 1);
  return loadFolder(0);
}
shared_ptr<Folder> FileSystem::getPathFolder(string& path){
  auto initialFolder = getInitialFolder(path);
  size_t pos;
  while((pos = path.find('/')) != string::npos){
    string folderName = path.substr(0, pos);
    path.erase(0, pos+1);
    initialFolder = initialFolder->getFolder(folderName);
    if(initialFolder == NULL)
      return NULL;
    initialFolder = loadFolder(initialFolder->getInitialBlock());
  }
  return initialFolder;
}
  
void FileSystem::initFileMap(){
  fileMap_.resize(FILE_BLOCKS);
  disk_.seekp(FILEMAP_POSITION);
  for(int i = 0; i < FILE_BLOCKS; i++){
    char next[6];
    disk_.read(next, 6);
    fileMap_[i] = atoi(next);
  }
}

void FileSystem::addMapRegistry(int block, int newBlock){
  fileMap_[block] = newBlock;
  stringstream buffer;
  buffer << setfill('0') << setw(5) << newBlock;
  disk_.seekp(FILEMAP_POSITION + block*6);
  disk_ << buffer.str();
}

vector<string> FileSystem::getFileChunks(string data){
  vector<string> vs;
  stringstream input(data);

  for(unsigned int i = 0; i < data.size(); i += BLOCK_SIZE-1)
    vs.push_back(data.substr(i, BLOCK_SIZE - 1));

  return vs;
}

int FileSystem::getNextFreeBlock(){
  if(!disk_.good())
    cout << "Morreu!\n";
  disk_.seekp(BITMAP_POSITION);
  char c = 1;
  for(int i=0; i < FILE_BLOCKS/8+1; i++){
    disk_.get(c);
    unsigned char value = (unsigned char) c;    
    unsigned int byte = (unsigned int) value;
    for (unsigned int j = 0; j < 8; j++){
      if(byte%2 == 0){        
        value = (unsigned int) value + (1 << j);
        disk_.seekp(BITMAP_POSITION + i);
        disk_.put((char) value);
        return i*8+j;
      }
      byte = byte/2;
    }
  }

  cout << "Disco cheio" << endl;
  exit(1);
  return 0;
}

string FileSystem::getFileData(int block){
  string data;
  do{
    char buffer[BLOCK_SIZE];
    disk_.seekp(block*BLOCK_SIZE);
    disk_.read(buffer, BLOCK_SIZE);
    data += buffer;
    block = fileMap_[block];
  } while (block != 0);
  return data;
}

void FileSystem::removeFile(int block){
  while(block != 0){
    char c;
    unsigned int value;
    int i = block/8;
    int j = block%8;
    disk_.seekp(BITMAP_POSITION + i);
    disk_.get(c);
    value = (unsigned int) c - (1 << j);
    disk_.seekp(BITMAP_POSITION + i);
    disk_.put((char) value);
    block = fileMap_[block];
  }
}

void FileSystem::close(){
  disk_.close();
}

void FileSystem::printInfo(){
  int diretorios = 0;
  int arquivos = 0;
  int virtualSize = getTotalSize(getCurrentFolder(), &diretorios, &arquivos);
  int emptySpace = getTotalEmptySpace();

  cout << "diretorios: " << diretorios << endl;
  cout << "arquivos: " << arquivos << endl;
  cout << "Espaço Livvre (bytes): " << emptySpace << endl;
  cout << "Espaço Desperdiçado (bytes): " << (FILE_BLOCKS*BLOCK_SIZE) - emptySpace - virtualSize << endl;
}

int FileSystem::getTotalSize(shared_ptr<Folder> folder, int* diretorios, int* arquivos){

  auto files = folder->getFiles();
  int size = 0;

  unsigned int i = (folder->getName() == "/" ?  0 : 1);

  for (; i < files.size(); i++){
    if(files[i]->isFolder()){
      *diretorios = *diretorios + 1;
      auto childFolder = loadFolder(files[i]->getInitialBlock());
      size += getTotalSize(childFolder, diretorios, arquivos);
    } else {
      *arquivos = *arquivos + 1;
      size += files[i]->getSize();
    }
  }

  return size;
}

int FileSystem::getTotalEmptySpace(){

  int emptySpace = 0;

  disk_.seekp(BITMAP_POSITION);
  char c;

  for(int i=0; i < FILE_BLOCKS/8+1; i++){
    disk_.get(c);
    unsigned char value = (unsigned char) c;    
    unsigned int byte = (unsigned int) value;
    for (unsigned int j = 0; j < 8; j++){
  
      if(byte%2 == 0){
        if(i*8+j <= FILE_BLOCKS)   
          emptySpace++;
      }
      byte = byte/2;
    }
  }
  return emptySpace*BLOCK_SIZE;
}