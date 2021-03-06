/************************
EP2 - SO
Vinícius Silva - 7557626
Mateus Barros - 7991037

*************************/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <string>
#include <memory>

#define PAGE_SIZE 16

struct MemorySlot{
  int pid, position, size;
  std::shared_ptr<MemorySlot> next;
  std::shared_ptr<MemorySlot> prev;

  MemorySlot(int a, int b, int c) : pid(a), position(b), size(c){}
};

struct Page{
  int posVirtual, posReal, pid, pageNumber = -1, accessNumber = -1;
  bool read;

  Page(int a, int b, int c, bool d) : posVirtual(a), posReal(b), pid(c), read(d){}
};

class Memory{
  
private:
  std::string filename_;
  int size_;

public:
  Memory(std::string , int);
  std::shared_ptr<MemorySlot> getMemoryState();
  void setMemoryState(std::shared_ptr<MemorySlot>);
  void print(std::string);
};

#endif // MEMORY_HPP
