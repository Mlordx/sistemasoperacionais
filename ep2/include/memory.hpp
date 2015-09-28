#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>

struct MemorySlot {
  int pid, position, size;
  MemorySlot* next;
  MemorySlot* prev;
  MemorySlot(int a, int b, int c) : pid(a), position(b), size(c){}
};

class Memory{
  
private:
  std::string filename_;
  int size_;

public:
  Memory(std::string , int);
  MemorySlot* getMemoryState();
  void setMemoryState(MemorySlot*);
};

#endif // MEMORY_HPP