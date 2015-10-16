#include <iostream>
#include <string>
#include <vector>
#include <jobFactory.hpp>
#include <memoryManager.hpp>
#include <simulator.hpp>

using namespace std;


int main(int argc,char** argv){
  int n, espaco, substitui;
  string cmd,arg;
  int virt;
  int tot;
  vector<Job> processes;
  shared_ptr<MemoryManager> mmu;
  JobFactory jobs(42);
  Simulator simulator;

  while(1){
    cout << "Insira comando: ";
    cin >> cmd;

    if( cmd == "carrega"){
      cin >> arg;
      processes = jobs.createJobsFromFile(arg,&tot,&virt);
      
    }else if( cmd == "espaco" ){
      cin >> espaco;
 
    }else if( cmd == "substitui"){
      cin >> substitui;
    }else if( cmd == "executa"){
      cin >> n;
      shared_ptr<MemoryManager> aux(new MemoryManager(tot, virt));
      mmu = aux;
      mmu->setMemoryAlgorithm(espaco);
      mmu->setPageAlgorithm(substitui);
      simulator.run(processes, mmu, n);
     
    }else if( cmd == "sai"){ break; }
    else{
      cout << "\nComando inválido!\n\n";
      cout << "-Comandos aceitos:\n";
      cout << "----carrega <arquivo>\n";
      cout << "----espaco <num>\n";
      cout << "----substitui <num>\n";
      cout << "----executa <intervalo>\n";
      cout << "----sai\n\n";
      continue;
    }
  }
  return 0;
}
