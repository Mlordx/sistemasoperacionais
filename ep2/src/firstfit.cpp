#include <firstfit.hpp>

void FirstFit(Memory mem,vector<Job> jobs){
  int time = 0;
  int i = 0;
  
  while(1){
    Job current_job = jobs[i];
    if( current_job.startTime_ == time ){
      shared_ptr<MemorySlot> head = getMemoryState();
      auto p = head;

      while(p != nullptr){
	auto aux = *(p);
	if(p.pid == -1){ //caso seja um espaço vazio
	  if(p.size < current_job.peakAccess()){//caso não caiba
	    p = p->next;
	    time++;
	    continue; 
	  }
	  else{
	    if( p.size > current_job.peakAccess() ){
	      p.size -= current_job.peakAccess();
	      MemorySlot new_mem(i,i,current_job.peakAccess());
	      auto aux2 = p.prev; //Adiciona no começo do trecho vazio
	      aux2.next = new_mem;
	      new_mem.prev = aux2;
	      new_mem.next = p;
	    }else{ //Igual
	      p.pid = i; // Simplesmente muda os campos do MemorySlot atual para representar que o processo ocupou todo esse espaço
	      p.pid = position;
		      
	    }
	  }
	  setMemoryState(head);
	}

      }

      i++;
    }
    time++;
    p = p->next;
  }

}
