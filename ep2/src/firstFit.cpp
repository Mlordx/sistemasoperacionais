#include <iostream>
#include <firstFit.hpp>
#include <jobFactory.hpp>

using namespace std;
FirstFit::FirstFit(shared_ptr<MemorySlot> head) : MemoryAlgorithm(head),list(head) {}


int FirstFit::execute(Job job){
  auto p = list;
  auto size = getRealSize(job);

  while(p != nullptr){
    auto aux = *(p);
    if(p->pid == -1 && p->size >= size){
	auto bla = insertJob(job,p);
	return bla->pid;
    }
    p = p->next;
  }
  return -1;
}
