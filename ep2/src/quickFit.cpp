#include <iostream>

#include <quickFit.hpp>
#include <jobFactory.hpp>

using namespace std;

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
      if(p->pid == -1){
        if(i == 4){
          memory_list[4].push_back(p);
      
      } else {
        if(i*16 < (unsigned)p->size && (unsigned)p->size <= (i+1)*16){
          memory_list[i].push_back(p);
        }
      }
      }
    }
    
    p = p->next;
  }
}

int QuickFit::execute(Job job){
  auto size = getRealSize(job);
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
