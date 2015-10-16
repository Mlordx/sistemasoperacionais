#include <iostream>
#include <string>
#include <vector>
#include <jobFactory.hpp>
#include <memoryManager.hpp>
#include <simulator.hpp>

using namespace std;

void imprimeDados(){

}

int main(int argc,char** argv){
  int n;
  string cmd,arg;
  int virt;
  int tot;
  vector<Job> processes;
  shared_ptr<MemoryManager> mmu;
  JobFactory jobs(42);
  Simulator simulator;

  int nJobs[3] = {25, 60, 100};

  for(int j = 0; j < 3; j++){
    cout << "\n-------------TAMANHO >> " << nJobs[j] << "---------------\n\n";
    for(int i = 0; i < 30; i++){
      // cout << "\n" << i << ": \n";
      processes = jobs.createJobsFromFile("testes/teste" + to_string(nJobs[j]) + "_" + to_string(i) + ".txt",&tot,&virt);
      n = 20;
      shared_ptr<MemoryManager> aux(new MemoryManager(tot, virt));
      mmu = aux;
      mmu->setMemoryAlgorithm(1);
      mmu->setPageAlgorithm(1);
      simulator.run(processes, mmu, n);
    }
  }

  return 0;
}
