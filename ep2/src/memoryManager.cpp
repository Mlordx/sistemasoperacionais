#include <iostream>
#include <vector>
#include "memoryManager.hpp"
#include "firstFit.hpp"
#include "nextFit.hpp"
#include "quickFit.hpp"
#include "notRecentlyUsedPage.hpp"
#include "firstInFirstOut.hpp"
#include "secondChance.hpp"
#include "leastRecentlyUsedPage.hpp"

#include "jobFactory.hpp"


using namespace std;

void MemoryManager::setReal(int sizeReal){
  Memory real(REAL_FILE, sizeReal);
  real_ = real.getMemoryState();
}

void MemoryManager::setVirtual(int sizeVirtual){
  Memory virt(VIRTUAL_FILE, sizeVirtual);
  virtual_ = virt.getMemoryState();
}

int MemoryManager::getRealSize(){
  return sizeReal_;
}

int MemoryManager::getVirtualSize(){
  return sizeVirtual_;
}

MemoryManager::MemoryManager(int sizeVirtual, int sizeReal){
  for(int i = 0; i < sizeVirtual; i+=PAGE_SIZE){
    pageTable_.push_back(Page(i, -1, -1, false));
  }
  
  sizeVirtual_ = sizeVirtual;
  sizeReal_ = sizeReal;

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  Memory real(REAL_FILE, sizeReal_);
  virtual_ = virt.getMemoryState();
  real_ = real.getMemoryState();
  nextPageNumber_ = 0;
  nextAccessNumber_ = 0;
  inserter_.reset(new NextFit(real_));
}

shared_ptr<MemorySlot> MemoryManager::getMemoryState(){
  return virtual_;
}

bool MemoryManager::insert(Job job){

  int position = memoryAlg_->execute(job);

  if(position == -1)
    return false;

  int page = position/PAGE_SIZE;
  int nPages = memoryAlg_->getRealSize(job)/PAGE_SIZE;

  for(int i = page; i < page + nPages; i++){
    if(i >= (int) pageTable_.size() || pageTable_[i].pid != -1){
      cout << "Memory allocation fail\n";
      exit(-1);
    }
    pageTable_[i].pid = job.getId();
    pageTable_[i].read = false;
  }

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  virt.setMemoryState(virtual_);

  return true;
}

bool MemoryManager::remove(Job job){
  
  if(!(removeFromPageTable(job) && removeFromMemory(job, virtual_))){
    return false;
  }
  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  Memory real(REAL_FILE, sizeReal_);
  virt.setMemoryState(virtual_);
  real.setMemoryState(real_);
  return true;

}

bool MemoryManager::removeFromPageTable(Job job){
  bool alterou = false;
  for(int i = 0; i < (int) pageTable_.size(); i++){
    if(pageTable_[i].pid == job.getId()){
      alterou = true;
      pageTable_[i].pid = -1;
      pageTable_[i].pageNumber = -1;
      if(pageTable_[i].posReal != -1){
        pageTable_[i].posReal = -1;
        alterou = alterou && removeFromMemory(job, real_);
      }
    }
  }

  return alterou;    
}

bool MemoryManager::removeFromMemory(Job job, shared_ptr<MemorySlot> memory){
  auto crawler = memory;
  auto prev = crawler;

  while(crawler != nullptr && crawler->pid != job.getId()){
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

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  virt.setMemoryState(memory);

  return true;
}

bool MemoryManager::read(Job& job, int position){

  for(int i = 0; i < (int) pageTable_.size(); i++){
    if(pageTable_[i].pid == job.getId()){
      position += pageTable_[i].posVirtual;
      break;
    }
  }

  int pageIn = position/16;
  pageTable_[pageIn].read = true;
  pageTable_[pageIn].accessNumber = nextAccessNumber_++;

  if(pageTable_[pageIn].posReal != -1)
    return true;

  job.memoryFail++;

  pageTable_[pageIn].pageNumber = nextPageNumber_++;  

  std::shared_ptr<Job> realJob(new Job);

  realJob->setId(pageTable_[pageIn].pid);
  realJob->setSize(PAGE_SIZE);
  pageTable_[pageIn].posReal = inserter_->execute(*realJob);

  if(pageTable_[pageIn].posReal == -1){
    swap(pageIn, pageAlg_->readPage(pageTable_, pageIn));
  }

  auto crawler = real_;
  
  while(crawler->position != pageTable_[pageIn].posReal){
    crawler = crawler->next;
  }
  
  crawler->pid = pageTable_[pageIn].pid;

  Memory real(REAL_FILE, sizeReal_);
  real.setMemoryState(real_);

  return true;

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

void MemoryManager::setPageAlgorithm(int pageAlgorithmIndex){
  
  switch(pageAlgorithmIndex){
    case 1:
      pageAlg_.reset(new NotRecentlyUsedPage); break;
    case 2:
      pageAlg_.reset(new FirstInFirstOut); break;
    case 3:
      pageAlg_.reset(new SecondChance); break;
    case 4:
      pageAlg_.reset(new LeastRecentlyUsedPage); break;
    default:
      cout << "Invalid page algorithm: " << pageAlgorithmIndex << endl;
      exit(-1);
  }
}

bool MemoryManager::swap(int in, int out){
  if(out == -1)
    return false;
  if(in == out)
    return true;
  pageTable_[in].posReal = pageTable_[out].posReal;
  pageTable_[out].posReal = -1;
  return true;
}

void MemoryManager::printMemoryState(){ 
  cout << "Legenda: (Posição,Tamanho,PID)\n\n";
 
  auto table = virtual_;
  cout << "Lista da memória física:\n";
  while(table != nullptr){
    cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
    table = table->next;
  }
  cout << endl << endl << endl;
  table = real_;
  cout << "Lista da memória virtual:\n";
  while(table != nullptr){
    cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
    table = table->next;
  }
  cout << endl << endl << endl;
}

void MemoryManager::printPageTable(){
  int i = 0;
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    if((*(page)).posReal == -1){
      i++;
      continue;
    }
    cout << i++ << ": "
    << (*(page)).pageNumber << ", "
    << (*(page)).pid << ", "
    << (*(page)).posVirtual << ", " 
    << (*(page)).posReal << ", " 
    << ((*(page)).read ? "true" : "false") << ", "
    << (*(page)).accessNumber << endl;
  }
}

void MemoryManager::reset(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    page->read = false;
  }
}
