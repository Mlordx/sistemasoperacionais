// #include <iostream>
// #include <string>
// #include <vector>

// using namespace std;

// #include <jobFactory.hpp>
// #include <memoryManager.hpp>
// #include <simulator.hpp>

// int main(int argc,char** argv){
//   int n, espaco, substitui;
//   string cmd,arg;
//   int virt;
//   int tot;
//   vector<Job> processes;
//   MemoryManager* mmu;
//   JobFactory jobs(42);
//   Simulator simulator;

//   while(1){
//     cout << "Insira comando: ";
//     cin >> cmd;

//     if( cmd == "carrega"){
//       cin >> arg;
//       processes = jobs.createJobsFromFile(arg,&tot,&virt);
      
//     }else if( cmd == "espaco" ){
//       cin >> espaco;
 
//     }else if( cmd == "substitui"){
//       cin >> substitui;
      
//     }else if( cmd == "executa"){
//       // processes = jobs.createJobsFromFile("testes/teste100.txt",&tot,&virt);
//       // mmu = new MemoryManager(tot, virt);
//       // espaco = 2;
//       // substitui = 4;
//       cin >> n;
//       mmu = new MemoryManager(tot, virt);
//       mmu->setMemoryAlgorithm(espaco);
//       mmu->setPageAlgorithm(substitui);
//       simulator.run(processes, mmu, n);
//       delete mmu;
//     }else if( cmd == "sai"){ break; }
//     else{
//       cout << "\nComando inválido!\n\n";
//       cout << "-Comandos aceitos:\n";
//       cout << "----carrega <arquivo>\n";
//       cout << "----espaco <num>\n";
//       cout << "----substitui <num>\n";
//       cout << "----executa <intervalo>\n";
//       cout << "----sai\n\n";
//       continue;
//     }
//   }
//   free(mmu);
//   return 0;
// }