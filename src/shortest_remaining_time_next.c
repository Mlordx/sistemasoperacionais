#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "shortest_remaining_time_next.h"

void srtn_run_thread(Job*, int);
Job* srtn_get_next_job();
int srtn_compare_jobs_by_duration(const void * a, const void * b);
int srtn_get_next_free_CPU();
void srtn_reorder_jobs();

Job** buffer;
int buffer_size = 0;
Job** running_jobs;
int* CPUs;
int num_CPU;
pthread_t* threads = NULL;
pthread_mutex_t* mutex = NULL;

int shortest_remaining_time_next(Job * jobs, int n, int* arg_CPUs, int arg_num_CPU, long int global_start, pthread_mutex_t* arg_mutex){
  
  int next = 0, busy_CPUs = 0, i;
  
  CPUs = arg_CPUs;
  num_CPU = arg_num_CPU;
  buffer = malloc(sizeof(Job*)*n);
  running_jobs = malloc(sizeof(Job*)*num_CPU);
  threads = malloc(sizeof(pthread_t)*num_CPU);
  mutex = arg_mutex;
  
  while(next < n || buffer_size > 0){
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      buffer[buffer_size++] = &jobs[next++];
      if(srtn_get_next_free_CPU() == -1)
        srtn_reorder_jobs(global_start);
    }
    while((i = srtn_get_next_free_CPU()) != -1 && buffer_size > 0){
        CPUs[i] = 1;
        srtn_run_thread(srtn_get_next_job(), i);
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < num_CPU; i++)
      busy_CPUs += CPUs[i];
  } while (busy_CPUs > 0);
  return 1;
}

Job* srtn_get_next_job(){
  qsort(buffer, buffer_size, sizeof(Job*), srtn_compare_jobs_by_duration);
  return buffer[--buffer_size];
}

int srtn_compare_jobs_by_duration(const void * a, const void * b){
  Job* A = *(Job**)a;
  Job* B = *(Job**)b;
  return A->duration < B->duration;
}

void srtn_run_thread(Job* job, int CPU_index){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  running_jobs[CPU_index] = job;
  job->real_start = define_start();
  pthread_create(&threads[CPU_index], NULL, simulate, (void *) args);
}

int srtn_get_next_free_CPU(){
  int i;
  for (i = 0; i < num_CPU; i++){
    if(!CPUs[i]) {
      return i;
    }
  }
  return -1;
}

void srtn_reorder_jobs(long int global_start){
  int i;

  for(i = 0; i < num_CPU; i++){
    pthread_mutex_lock(&mutex[0]);
    if(CPUs[i]){
      pthread_cancel(threads[i]);
      CPUs[i] = 0;
      running_jobs[i]->duration -= time_diff(running_jobs[i]->real_start)/1000.0;
      if(running_jobs[i]->duration < 0.01){
        running_jobs[i]->duration = 0.01;
      }
      buffer[buffer_size++] = running_jobs[i];
    }
    pthread_mutex_unlock(&mutex[0]);
  }
}
