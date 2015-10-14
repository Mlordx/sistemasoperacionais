#include <iostream>
#include <vector>
#include "memoryManager.hpp"
#include "firstFit.hpp"
#include "nextFit.hpp"
#include "quickFit.hpp"
#include "notRecentlyUsedPage.hpp"

#include "jobFactory.hpp"


using namespace std;

int main(){
  MemoryManager manager(256, 64);
  JobFactory factory = JobFactory(40);
  auto jobs = factory.createManyJobsRandomly(5, 20, "processo_", 50, 10, 40);
  manager.setMemoryAlgorithm(2);
  manager.setPageAlgorithm(1);

  for(int i = 0; i < 10; i++){
    cout << "\ninserindo job: " << i << endl << endl;
    if(!manager.insert(jobs[i])){
      cout << "Não foi possível inserir\n";
      exit(-1);
    }
    cout << "lendo: " << jobs[i].getId() << "\n";
    if(!manager.read(jobs[i], 0)){
      cout << "Não foi possível ler\n";
      exit(-1); 
    }
    manager.printMemoryState();
    manager.printPageTable();
    if(i > 0 && i%3 == 0){
      cout << "\nremovendo job: " << i << endl << endl;
      if(!manager.remove(jobs[i-3])){
        cout << "falhou\n";
        exit(-1);
      }
      manager.printPageTable();
      // manager.printMemoryState();
    }
    std::cin.ignore();
  }

  return 0;
}

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
  nextPageNumber_ = 0;
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
    pageTable_[i].pageNumber = nextPageNumber_++;
  }

  Memory virt(VIRTUAL_FILE, sizeVirtual_);
  virt.setMemoryState(virtual_);

  return true;
}

bool MemoryManager::remove(Job job){
  
  return removeFromPageTable(job) && removeFromMemory(job, virtual_);
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

  cout << "procurando: " << job.getId() << endl;

  while(crawler != nullptr && crawler->pid != job.getId()){
    cout << "verificado: " << crawler->pid << endl;
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

bool MemoryManager::read(Job job, int position){


  for(int i = 0; i < (int) pageTable_.size(); i++){
    if(pageTable_[i].pid == job.getId()){
      position += pageTable_[i].posVirtual;
      break;
    }
  }

  int pageIn = position/16;
  pageTable_[pageIn].read = true;

  if(pageTable_[pageIn].posReal != -1)
    return true;

  std::shared_ptr<Job> realJob(new Job);

  realJob->setId(pageTable_[pageIn].pid);
  realJob->setSize(PAGE_SIZE);
  pageTable_[pageIn].posReal = inserter_->execute(*realJob);

  if(pageTable_[pageIn].posReal == -1){
    cout << "swapping\n";
    swap(pageIn, pageAlg_->readPage(pageTable_, pageIn));
  }

  auto crawler = real_;
  
  while(crawler->position != pageTable_[pageIn].posReal)
    crawler = crawler->next;
  
  crawler->pid = pageTable_[pageIn].pid;
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
  cout << "in: " << in << endl;
  cout << "out: " << out << endl;

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
  table = real_;
  while(table != nullptr){
    cout << "(" << table->position << ", " << table->size << ", " << table->pid << ") ";
    table = table->next;
  }
  cout << endl << endl << endl;
}

void MemoryManager::printPageTable(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    cout << (*(page)).posVirtual << ", " << (*(page)).posReal << ", " << (*(page)).pid << endl;
  }
}

void MemoryManager::reset(){
  for(auto page = pageTable_.begin(); page != pageTable_.end(); page++){
    page->read = false;
  }
}
