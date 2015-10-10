#include <iostream>
#include "memoryAlgorithm.hpp"

using namespace std;

MemoryAlgorithm::MemoryAlgorithm(shared_ptr<MemorySlot> memorySlot){
  head_ = memorySlot;
}

shared_ptr<MemorySlot> MemoryAlgorithm::insertJob(Job job, shared_ptr<MemorySlot> memorySlot){
  
  if(memorySlot->size < getRealSize(job)){
    cout << "Erro na alocação de memória\n";
    exit(-1);
  }

  int remainderSize = memorySlot->size - getRealSize(job);
  int remainderPosition = memorySlot->position + getRealSize(job);

  memorySlot->size = getRealSize(job);
  memorySlot->pid = job.getId();

  if(remainderSize == 0) return memorySlot;

  shared_ptr<MemorySlot> remainder(new MemorySlot(-1,remainderPosition,remainderSize));

  remainder->next = memorySlot->next;
  memorySlot->next = remainder;

  return memorySlot;
}

int MemoryAlgorithm::getRealSize(Job job){
  int numPages = job.getSize()/16;
  if(job.getSize()%16 != 0)
    numPages++;
  return numPages * 16;
}
