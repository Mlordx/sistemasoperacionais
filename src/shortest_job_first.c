#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "scheduler.h"

void run_shortest_thread(Job, int);
Job get_next_job(Job*, int*);
int compare_jobs_by_duration(const void * a, const void * b);

int shortest_job_first(Job * jobs, int n, int* CPUs, int numCPU, long int global_start){
  int next = 0, bufferSize = 0, CPU_ocupados = 0, i;
  Job* buffer = malloc (sizeof(Job)*n);
  
  while(next < n || bufferSize > 0){
    if(time_diff(global_start) > jobs[next].arrival*1000 && next < n){
      buffer[bufferSize++] = jobs[next++];
    }
    for(i = 0; i < numCPU; i++){
      if(!CPUs[i] && bufferSize > 0){
          CPUs[i] = 1;
          run_shortest_thread(get_next_job(buffer, &bufferSize), i);
          break;
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

Job get_next_job(Job* buffer, int* bufferSize){
  int i;
  qsort(buffer, *bufferSize, sizeof(Job), compare_jobs_by_duration);
  /*printf("------------------------------------------------------\n\n");
  for(i = 0; i < *bufferSize; i++){
    printf("%f, %d\n", buffer[i].duration, i);
  }
  printf("\n"); */
  return buffer[--(*bufferSize)];
}

int compare_jobs_by_duration(const void * a, const void * b){
  Job A = *(Job*)a;
  Job B = *(Job*)b;
  return A.duration < B.duration;
}

void run_shortest_thread(Job job, int CPU_index){  
  Data* args;
  pthread_t thread;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  pthread_create(&thread, NULL, simulate, (void *) args);
}