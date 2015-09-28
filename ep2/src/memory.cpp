#include <iostream>
#include <fstream>

#include "memory.hpp"

using namespace std;

typedef char byte;

void initialize(string, int);
void write(MemorySlot*, byte*);

Memory::Memory(string filename, int size){
  filename_ = filename;
  size_ = size;
  setMemoryState(NULL);
}

void Memory::setMemoryState(MemorySlot* memorySlot){
  
  ofstream file;
  file.open(filename_, ios::binary);
  
  byte* bytes = (byte*) malloc(sizeof(byte)*size_);
  
  for(int i = 0; i < size_; i++)
    bytes[i] = -1;
  
  while(memorySlot != NULL){
    cout << "memorySlot: " << memorySlot->pid << endl;  
    write(memorySlot, bytes);
    memorySlot = memorySlot->next;
  }

  file.write(bytes, size_);
  file.close();
}

MemorySlot* Memory::getMemoryState(){
  
  ifstream file;
  byte* bytes = (byte*) malloc(sizeof(byte)*size_);
  
  file.open(filename_, ios::binary);
  file.read(bytes, size_);
  file.close();

  byte lastpid = -1;
  int size = 0, pos = 0;
  MemorySlot* mem = new MemorySlot(-1, 0, 0);
  MemorySlot* head = mem;

  for(int i = 0; i < size_; i++){
    if(bytes[i] != lastpid){
      if(size > 0){
        mem->next = new MemorySlot((int) lastpid, pos, size);
        mem = mem->next;
      }
      size = 0;
      pos = i;
      lastpid = bytes[i];
    }
    size++;
  }

  mem->next = new MemorySlot((int) lastpid, pos, size);
  mem = mem->next;
  mem->next = NULL;

  return head->next;
}

void write(MemorySlot* mem, byte* bytes){
  int size = mem->position + mem->size;
  for(int i = mem->position; i < size; i++)
    bytes[i] = mem->pid;
}