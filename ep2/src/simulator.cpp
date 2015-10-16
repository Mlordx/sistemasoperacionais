#include <iostream>
#include <thread> 
#include <chrono>
#include "simulator.hpp"

using namespace std;

void Simulator::run(vector<Job>& jobs, shared_ptr<MemoryManager> manager, int print){
  int i = 0;

  Memory virt(VIRTUAL_FILE, manager->getVirtualSize());
  Memory real(REAL_FILE, manager->getRealSize());

  while(!jobs.empty() || !running_.empty()){
    if(!insert(manager, jobs, i)){
      cout << "Error: Out of Memory\n";
      exit(-1);
    }
    if(!read(manager, jobs, i)){
      cout << "Error: Memory fail.\n";
      exit(-1);
    }
    if(!remove(manager, jobs, i)){
      cout << "Error: Memory fail.\n";
      exit(-1);
    }
    if(i % print == 0){
      // cout << "\n-------------SEGUNDO " << i << "---------------\n\n";
      // manager->printMemoryState();
      // virt.print("Virtual");
      // real.print("Real");
    }
    i++;
    if(i % 3 == 0){
      manager->reset();
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

bool Simulator::insert(shared_ptr<MemoryManager> manager, vector<Job>& jobs, int turn){
  for(auto job = jobs.begin(); job != jobs.end();){
    if(job->getStartTime() == turn){
      running_.push_back(*job);
      if(!manager->insert(*job))
        return false;
      jobs.erase(job);
    } else {
      job++;
    }
  }
  return true;
}

bool Simulator::read(shared_ptr<MemoryManager> manager, vector<Job>& jobs, int turn){
  for(auto job = running_.begin(); job != running_.end(); job++){
    if(job->hasAccesses() && job->peakAccess().time == turn){
      auto access = job->getNextAccess();
      if(!manager->read(*job, access.position))
        return false;
    }
  }
  return true;
}

bool Simulator::remove(shared_ptr<MemoryManager> manager, vector<Job>& jobs, int turn){
  for(auto job = running_.begin(); job != running_.end();){
    if(job->getEndTime() == turn){
      if(!manager->remove(*job))
        return false;
      else
        cout << job->memoryFail << ";";
      running_.erase(job);
    }else{
      job++;
    }
  }
  return true;
}
