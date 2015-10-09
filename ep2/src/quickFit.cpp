#include <iostream>

#include <quickFit.hpp>
#include <jobFactory.hpp>

using namespace std;

int main(){
  cout << "teste\n";
  JobFactory factory(10);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  Memory mem("teste.mem", 1000);
  auto head = mem.getMemoryState();
  auto table = head;
  QuickFit algorithm(head);


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
    algorithm.updateMemoryList(head);
  }
  
  return 0;
}


QuickFit::QuickFit(shared_ptr<MemorySlot> hd) : MemoryAlgorithm(hd),head(hd) {
  memory_list.resize(5);
  updateMemoryList(head);
}

void QuickFit::updateMemoryList(shared_ptr<MemorySlot> head){
  memory_list.clear();
  memory_list.resize(5);
  
  auto p = head;
  
  while(p != nullptr){
    
    for(unsigned int i = 0; i < 5; i++){
      if(i == 4){
	memory_list[4].push_back(p);

      }else{
	if(i*16 < (unsigned)p->size && (unsigned)p->size <= (i+1)*16){
	  memory_list[i].push_back(p);
	}
      }
    }
    p = p->next;
  }
}

int QuickFit::execute(Job job){
  auto size = job.getSize();
  unsigned int i = size/16;

  if(i >= memory_list.size()) i = memory_list.size()-1;

  
  while( memory_list[i].empty() ) i++; //procura uma lista maior para o processo caso a lista ideal dele esteja vazia;

  for(unsigned int a = 0; a < memory_list[i].size(); a++){
    shared_ptr<MemorySlot> slot(memory_list[i][a]);
    if(slot->size >= size){
      auto aux = insertJob(job,slot);
      return aux->position;
    }
  }
    return -1;
}
