#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "scheduler.h"

void run_thread(pthread_t, Job, int);

int first_in_first_out(Job * jobs, int n, int* CPUs, int numCPU, long int global_start){
  int i = 0, next = 0, CPU_ocupados = 0;
  pthread_t* threads = malloc(sizeof(pthread_t)*n); 
  
  while(next < n){
    for(i = 0; i < numCPU; i++){
      if(!CPUs[i]){
        if(time_diff(global_start) > jobs[next].arrival*1000){
          CPUs[i] = 1;
          run_thread(threads[next], jobs[next], i);
          next++;
        }
      }
    }
  }

  do{
    CPU_ocupados = 0;
    for(i = 0; i < numCPU; i++)
      CPU_ocupados += CPUs[i];
  } while (CPU_ocupados > 0);

  return 1;
}

void run_thread(pthread_t thread, Job job, int CPU_index){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  pthread_create(&thread, NULL, simulate, (void *) args);
}