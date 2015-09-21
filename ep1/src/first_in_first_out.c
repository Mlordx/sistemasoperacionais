  #include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "scheduler.h"

void run_thread(pthread_t, Job*, int, FILE*);

int first_in_first_out(Job * jobs, int n, int* CPUs, int numCPU, long int global_start,FILE* output){
  int i = 0, next = 0, busy_CPUs = 0, nextToArive = 0;
  pthread_t* threads = malloc(sizeof(pthread_t)*n); 
  
  while(next < n){
    for(i = 0; i < numCPU; i++){
      if(nextToArive < n && time_diff(global_start) >= jobs[nextToArive].arrival*1000){
        if(get_debug()) fprintf(stderr,"O processo %s(linha: %d) chegou\n",*(&jobs[nextToArive].name),*(&jobs[nextToArive].line));
        nextToArive++;
      }
      if(nextToArive > next && !CPUs[i]){
        if(get_debug()) fprintf(stderr,"A cpu %d foi ocupada pelo processo %s\n", i, *(&jobs[next].name));
        CPUs[i] = 1;
        run_thread(threads[next], &jobs[next], i, output);
        next++;
      }
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < numCPU; i++)
      busy_CPUs += CPUs[i];
  } while (busy_CPUs > 0);

  return 1;
}

void run_thread(pthread_t thread, Job* job, int CPU_index, FILE* output){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  pthread_create(&thread, NULL, simulate, (void *) args);
}
