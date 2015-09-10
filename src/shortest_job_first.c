#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "scheduler.h"
#include "shortest_job_first.h"

void run_shortest_thread(Job*, int, FILE*);
Job* get_next_job(Job**, int*);
int compare_jobs_by_duration(const void * a, const void * b);

int shortest_job_first(Job * jobs, int n, int* CPUs, int numCPU, long int global_start,FILE* output){
  int next = 0, bufferSize = 0, busy_CPUs = 0, i;
  Job** buffer = malloc (sizeof(Job*)*n);
  
  while(next < n || bufferSize > 0){
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      buffer[bufferSize++] = &jobs[next++];
    }
    for(i = 0; i < numCPU; i++){
      if(!CPUs[i] && bufferSize > 0){
          CPUs[i] = 1;
          run_shortest_thread(get_next_job(buffer, &bufferSize), i,output);
          break;
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

Job* get_next_job(Job** buffer, int* bufferSize){
  qsort(buffer, *bufferSize, sizeof(Job*), compare_jobs_by_duration);
  return buffer[--(*bufferSize)];
}

int compare_jobs_by_duration(const void * a, const void * b){
  Job* A = *(Job**)a;
  Job* B = *(Job**)b;
  return A->duration < B->duration;
}

void run_shortest_thread(Job* job, int CPU_index,FILE* output){  
  Data* args;
  pthread_t thread;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  pthread_create(&thread, NULL, simulate, (void *) args);
}
