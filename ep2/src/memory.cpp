#include <iostream>
#include <fstream>
#include <vector>

#include "memory.hpp"

using namespace std;

typedef char byte;

void initialize(string, int);
void write(shared_ptr<MemorySlot>, vector<byte>&);

Memory::Memory(string filename, int size){
  filename_ = filename;
  size_ = size;
  setMemoryState(nullptr);
}

void Memory::setMemoryState(shared_ptr<MemorySlot> memorySlot){
  
  ofstream file;
  file.open(filename_, ios::binary);
    
  vector<byte> bytes(size_,-1);
  
  while(memorySlot != nullptr){
    cout << "memorySlot: " << memorySlot->pid << endl;  
    write(memorySlot, bytes);
    memorySlot = memorySlot->next;
  }

  file.write(&bytes[0], size_);
  file.close();
  
}

shared_ptr<MemorySlot> Memory::getMemoryState(){
  
  ifstream file;
  byte* bytes = (byte*) malloc(sizeof(byte)*size_);

  
  file.open(filename_, ios::binary);
  file.read(bytes, size_);
  file.close();

  byte lastpid = -1;
  int size = 0, pos = 0;
  shared_ptr<MemorySlot> mem(new MemorySlot(-1,0,0));
  shared_ptr<MemorySlot> head(mem);

  for(int i = 0; i < size_; i++){
    if(bytes[i] != lastpid){
      if(size > 0){
	shared_ptr<MemorySlot> aux(new MemorySlot((int) lastpid,pos,size));
	mem->next = aux;
        mem = mem->next;
      }
      size = 0;
      pos = i;
      lastpid = bytes[i];
    }
    size++;
  }


  shared_ptr<MemorySlot> aux(new MemorySlot((int) lastpid,pos,size));
  mem->next = aux;
  mem = mem->next;
  mem->next = nullptr;

  return head->next;
}

void write(shared_ptr<MemorySlot> mem, vector<byte>& bytes){
  int size = mem->position + mem->size;
  for(int i = mem->position; i < size; i++)
    bytes[i] = mem->pid;
}
