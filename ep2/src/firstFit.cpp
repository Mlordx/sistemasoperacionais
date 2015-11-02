#include <iostream>
#include <firstFit.hpp>
#include <jobFactory.hpp>

using namespace std;
FirstFit::FirstFit(shared_ptr<MemorySlot> head) : MemoryAlgorithm(head),list(head) {}


int FirstFit::execute(Job job){
  auto memoryTable = head_;
  while(memoryTable != nullptr){
    if(memoryTable->pid == -1 && memoryTable->size >= getRealSize(job)){
      memoryTable = insertJob(job, memoryTable);
      return memoryTable->position;
    }
    memoryTable = memoryTable->next;
  }
  return -1;
}
