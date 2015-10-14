#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <memory>
#include "memory.hpp"
#include "job.hpp"
#include "memoryAlgorithm.hpp"
#include "pageAlgorithm.hpp"

#define INTERVAL 1
#define PAGE_SIZE 16
#define REAL_FILE "ep2.mem"
#define VIRTUAL_FILE "ep2.vir"

class MemoryManager{
private:
  int sizeVirtual_;
  int sizeReal_;
  int nextPageNumber_;
  std::shared_ptr<MemorySlot> virtual_;
  std::shared_ptr<MemorySlot> real_;
  std::vector<Page> pageTable_;
  std::shared_ptr<PageAlgorithm> pageAlg_;
  std::shared_ptr<MemoryAlgorithm> memoryAlg_;
  bool swap (int, int);
  bool removeFromPageTable (Job);
  bool removeFromMemory (Job, std::shared_ptr<MemorySlot>);
public:
  MemoryManager(int, int);
  std::shared_ptr<MemorySlot> getMemoryState();
  void setPageAlgorithm(int);
  void setMemoryAlgorithm(int);
  void printMemoryState();
  void printPageTable();
  void setReal(int);
  void setVirtual(int);
  bool insert(Job);
  bool remove(Job);
  bool read(Job, int);
  void reset();
};

#endif // MEMORY_MANAGER_HPP
