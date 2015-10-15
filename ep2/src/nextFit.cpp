#include <iostream>
#include "nextFit.hpp"
#include "jobFactory.hpp"

using namespace std;

NextFit::NextFit(shared_ptr<MemorySlot> head) : MemoryAlgorithm(head), next_(head) {}

int NextFit::execute(Job job){
  auto memoryTable = next_;
  do{
    if(memoryTable->pid == -1 && memoryTable->size >= getRealSize(job)){
      next_ = insertJob(job, memoryTable);
      return next_->position;
    }
    memoryTable = memoryTable->next;
    if(memoryTable == nullptr)
      memoryTable = head_;
  } while(memoryTable != next_);

  return -1;
}
