#include <iostream>
#include "nextFit.hpp"
#include "jobFactory.hpp"

using namespace std;

/*
int main(){
  cout << "teste\n";
  JobFactory factory(50);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  Memory mem("teste.mem", 1024);
  auto head = mem.getMemoryState();
  auto table = head;
  NextFit algorithm(head);

  for(int i = 0; i < 40; i++){
    cout << algorithm.execute(jobs[i]) << endl;
    while(table != nullptr){
      cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
      table = table->next;
    }
    cout << endl << endl << endl;
    table = head;
    mem.setMemoryState(head);
  }
  
  return 0;
}
*/

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
