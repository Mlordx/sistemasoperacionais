#include <iostream>
#include <firstFit.hpp>
#include <jobFactory.hpp>

using namespace std;
/*
int main(){
  cout << "teste\n";
  JobFactory factory(40);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  Memory mem("teste.mem", 1000);
  auto head = mem.getMemoryState();
  auto table = head;
  FirstFit algorithm(head);

  int i = 0;
  for(;i < 40; i++){
    cout << algorithm.execute(jobs[i]) << endl;
    while(table != nullptr){
      cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
      table = table->next;
    }
    cout << endl << endl;
    table = head;
    mem.setMemoryState(head);
  }
  
  return 0;
}
*/
FirstFit::FirstFit(shared_ptr<MemorySlot> head) : MemoryAlgorithm(head),list(head) {}


int FirstFit::execute(Job job){
  auto p = list;
  auto size = job.getSize();

  while(p != nullptr){
    auto aux = *(p);
    if(p->pid == -1){ 
      if(p->size < size){
	p = p->next;
	continue; 
      }
      else{
	auto bla = insertJob(job,p);
	return bla->pid;
      }
    }
    p = p->next;
  }
  return -1;
}
