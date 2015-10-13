#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <jobFactory.hpp>
#include <memoryManager.hpp>
/*
int main(int argc,char** argv){
  int n;
  string cmd,arg;
  int a = 0;
  int* virt = &a;
  int* tot = &a;
  vector<Job> processes;
  MemoryManager mmu(0,0);
  JobFactory jobs(42);

  while(1){
    cout << "Insira comando: ";
    cin >> cmd;

    if( cmd == "carrega"){
      cin >> arg;
      processes = jobs.createJobsFromFile(arg,tot,virt);
      mmu.setReal(*tot);
      mmu.setVirtual(*virt);
      
      
    }else if( cmd == "espaco" ){
      cin >> n;
      mmu.setMemoryAlgorithm(n);
 
    }else if( cmd == "substitui"){
      cin >> n;
      mmu.setPageAlgorithm(n);
      
    }else if( cmd == "executa"){
      cin >> n;
      //roda o arquivo e imprime de n em n >segundos< 

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
*/
