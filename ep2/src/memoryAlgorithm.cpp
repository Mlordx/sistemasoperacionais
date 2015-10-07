#include <iostream>
#include "memoryAlgorithm.hpp"

using namespace std;

MemoryAlgorithm::MemoryAlgorithm(shared_ptr<MemorySlot> memorySlot){
  head_ = memorySlot;
}

shared_ptr<MemorySlot> MemoryAlgorithm::insertJob(Job job, shared_ptr<MemorySlot> memorySlot){
  
  if(memorySlot->size < job.getSize()){
    cout << "Erro na alocação de memória\n";
    exit(-1);
  }

  int remainderSize = memorySlot->size - job.getSize();
  int remainderPosition = memorySlot->position + job.getSize();

  memorySlot->size = job.getSize();
  memorySlot->pid = job.getId();

  if(remainderSize == 0)
    return memorySlot;

  shared_ptr<MemorySlot> remainder(new MemorySlot(-1,remainderPosition,remainderSize));

  remainder->next = memorySlot->next;
  memorySlot->next = remainder;

  return memorySlot;
}
