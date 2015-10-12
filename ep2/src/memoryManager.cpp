#include <iostream>
#include <vector>
#include "memoryManager.hpp"
#include "firstFit.hpp"
#include "nextFit.hpp"
#include "quickFit.hpp"

#include "jobFactory.hpp"


using namespace std;

/*
int main(){
  MemoryManager manager(1024, 258);
  JobFactory factory = JobFactory(40);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  manager.setMemoryAlgorithm(1);

  for(int i = 0; i < 40; i++){
    manager.insert(jobs[i]);
    if(i > 0 && i%3 == 0)
      manager.remove(jobs[i-3]);
  }

  return 0;
}
*/

void MemoryManager::setReal(int sizeReal){
  Memory real(REAL_FILE, sizeReal);
  real_ = real.getMemoryState();
}

void MemoryManager::setVirtual(int sizeVirtual){
  Memory virt(VIRTUAL_FILE, sizeVirtual);
  virtual_ = virt.getMemoryState();
}

MemoryManager::MemoryManager(int sizeVirtual, int sizeReal){
  
  for(int i = 0; i < sizeVirtual; i+=PAGE_SIZE){
    pageTable_.push_back(Page(i, -1, -1, false));
  }
  Memory virt(VIRTUAL_FILE, sizeVirtual);
  Memory real(REAL_FILE, sizeReal);
  virtual_ = virt.getMemoryState();
  real_ = real.getMemoryState();
}

shared_ptr<MemorySlot> MemoryManager::getMemoryState(){
  return virtual_;
}


void MemoryManager::setMemoryAlgorithm(int memoryAlgorithmIndex){
  switch(memoryAlgorithmIndex){
    case 1:
      memoryAlg_.reset(new FirstFit(virtual_)); break;
    case 2:
      memoryAlg_.reset(new NextFit(virtual_)); break;
    case 3:
      memoryAlg_.reset(new QuickFit(virtual_)); break;
    default:
      cout << "Invalid memory algorithm: " << memoryAlgorithmIndex << endl;
      exit(-1);
  }
}

bool MemoryManager::insert(Job job){
  cout << "inserindo: " << job.getId() << endl;
  int position = memoryAlg_->execute(job);
  if(position == -1) return false;
  printMemoryState();

  int page = position/PAGE_SIZE;
  int nPages = memoryAlg_->getRealSize(job)/PAGE_SIZE;

  for(int i = page; i < page + nPages; i++){
    if(i >= (int) pageTable_.size() /*|| pageTable_[i].pid != -1*/){
      cout << "Memory allocation fail\n";
      exit(-1);
    }
    pageTable_[i].pid = job.getId();
  }

  return true;
}

bool MemoryManager::remove(Job job){
  cout << "removendo: " << job.getId() << endl;
  //int pages = memoryAlg_->getRealSize(job)/PAGE_SIZE;
  auto crawler = virtual_;
  auto prev = crawler;

  while(crawler->pid != job.getId() && crawler != nullptr){
    prev = crawler;
    crawler = crawler->next;
  }
  
  if(crawler == nullptr)
    return false;

  crawler->pid = -1;
  if(prev != crawler && prev->pid == -1)
    crawler = prev;

  while(crawler->next != nullptr && crawler->next->pid == -1){
    auto next = crawler->next;
    crawler->size += next->size;
    crawler->next = next->next;
  }

  printMemoryState();
  return true;
}

void MemoryManager::printMemoryState(){
  
  auto table = virtual_;
  while(table != nullptr){
    cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
    table = table->next;
  }
  cout << endl << endl << endl;
}

void MemoryManager::printPageTable(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    cout << (*(page)).posVirtual << ", " << (*(page)).pid << endl;
  }
}
