#include <iostream>
#include <vector>
#include "memoryManager.hpp"
#include "firstFit.hpp"
#include "nextFit.hpp"
#include "quickFit.hpp"
#include "notRecentlyUsedPage.hpp"

#include "jobFactory.hpp"


using namespace std;

/*
int main(){
  MemoryManager manager(256, 64);
  JobFactory factory = JobFactory(40);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  manager.setMemoryAlgorithm(2);
  manager.setPageAlgorithm(1);

  for(int i = 0; i < 10; i++){
    manager.insert(jobs[i]);
    if(i > 0 && i%3 == 0)
      manager.remove(jobs[i-3]);
  }

  for(int i = 0; i < 100; i++){
    int ler = rand() % 258 + 1;
    cout << "Lendo : " << ler << endl;
    manager.read(ler);
    if(i%10 == 0)
      manager.reset();
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
  
  sizeVirtual_ = sizeVirtual;
  sizeReal_ = sizeReal;

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  Memory real(REAL_FILE, sizeReal_);
  virtual_ = virt.getMemoryState();
  real_ = real.getMemoryState();
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
    if(i >= (int) pageTable_.size() /*|| pageTable_[i].pid != -1*/){
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

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  virt.setMemoryState(virtual_);
  return true;
}

bool MemoryManager::read(int position){

  int pageIn = position/16;
  pageTable_[pageIn].read = true;

  if(pageTable_[pageIn].posReal != -1)
    return true;

  NextFit inserter(real_);
  std::shared_ptr<Job> realJob(new Job);
  realJob->setId(pageTable_[pageIn].pid)->setSize(PAGE_SIZE);
  pageTable_[pageIn].posReal = inserter.execute(*realJob);


  if(pageTable_[pageIn].posReal == -1)
    swap(pageIn, pageAlg_->readPage(pageTable_, pageIn));  
  
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
  
  auto table = virtual_;
  while(table != nullptr){
    cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
    table = table->next;
  }
  cout << endl << endl << endl;
}

void MemoryManager::printPageTable(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    cout << (*(page)).posVirtual << ", " << (*(page)).posReal << ", " << (*(page)).read << endl;
  }
}

void MemoryManager::reset(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    page->read = false;
  }
}
