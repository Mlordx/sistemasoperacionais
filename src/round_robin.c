#define QUANTUM 1000
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "time_handler.h"
#include "round_robin.h"

void rr_run_thread(Job*, int,FILE*);
Job* rr_get_next_job();
int rr_compare_jobs_by_duration(const void * a, const void * b);
int rr_get_next_free_CPU();
void rr_reorder_jobs();

Job** buffer;
int buffer_size_rr = 0;
Job** running_jobs;
int* CPUs;
int num_CPU;
pthread_t* threads_rr = NULL;
pthread_mutex_t* mutex_rr = NULL;

int round_robin(Job * jobs, int n, int* arg_CPUs, int arg_num_CPU, long int global_start, pthread_mutex_t* arg_mutex,FILE* output){
  
  int next = 0, busy_CPUs = 0, i;
  
  CPUs = arg_CPUs;
  num_CPU = arg_num_CPU;
  buffer = malloc(sizeof(Job*)*n);
  running_jobs = malloc(sizeof(Job*)*num_CPU);
  threads_rr = malloc(sizeof(pthread_t)*num_CPU);
  mutex_rr = arg_mutex;
  
  while(next < n || buffer_size_rr > 0){
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      //fprintf(output,"O processo %s foi colocado no buffer\n",*(&jobs[next].name));
      buffer[buffer_size_rr++] = &jobs[next++];
      if(rr_get_next_free_CPU() == -1 && time_diff(global_start) >= QUANTUM) rr_reorder_jobs(global_start);
    }
    while((i = rr_get_next_free_CPU()) != -1 && buffer_size_rr > 0){
        CPUs[i] = 1;
        rr_run_thread(rr_get_next_job(), i,output);
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < num_CPU; i++)
      busy_CPUs += CPUs[i];
  } while (busy_CPUs > 0);
  return 1;
}

Job* rr_get_next_job(){
  //print_job(buffer[buffer_size_rr-1]);
  return buffer[--buffer_size_rr];
}

void rr_run_thread(Job* job, int CPU_index,FILE* output){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  running_jobs[CPU_index] = job;
  job->real_start = define_start();
  pthread_create(&threads_rr[CPU_index], NULL, simulate, (void *) args);
}

int rr_get_next_free_CPU(){
  int i;
  for (i = 0; i < num_CPU; i++){
    if(!CPUs[i]) {
      return i;
    }
  }
  return -1;
}

void rr_reorder_jobs(long int global_start){
  int i; 

  for(i = 0; i < num_CPU; i++){
    pthread_mutex_lock(&mutex_rr[0]);
    if(CPUs[i]){
      pthread_cancel(threads_rr[i]);
      CPUs[i] = 0;
      
      running_jobs[i]->duration -= QUANTUM/1000.0;
      if(running_jobs[i]->duration < 0.01){
        running_jobs[i]->duration = 0.01;
      }

      buffer[buffer_size_rr++] = running_jobs[i];
    }
    pthread_mutex_unlock(&mutex_rr[0]);
  }
}
