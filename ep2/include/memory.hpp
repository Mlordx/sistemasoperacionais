#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <memory>


struct MemorySlot{
  int pid, position, size;
  std::shared_ptr<MemorySlot> next;
  std::shared_ptr<MemorySlot> prev;
  MemorySlot(int a, int b, int c) : pid(a), position(b), size(c){}
};

class Memory{
  
private:
  std::string filename_;
  int size_;

public:
  Memory(std::string , int);
  std::shared_ptr<MemorySlot> getMemoryState();
  void setMemoryState(std::shared_ptr<MemorySlot>);
};

#endif // MEMORY_HPP
