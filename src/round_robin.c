#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "round_robin.h"

#define QUANTUM 100

void rr_run_thread(Job*, int, FILE*);
Job* rr_get_next_job();
int rr_compare_jobs_by_slack_time(const void * a, const void * b);
int rr_get_next_free_CPU();
void rr_reorder_jobs();
double rr_get_slack_time(Job* job);

Job** rr_buffer;
int rr_buffer_size = 0;
Job** rr_running_jobs;
int* rr_CPUs;
int rr_num_CPU;
pthread_t* rr_threads = NULL;
pthread_mutex_t* rr_mutex = NULL;
long int rr_global_start;

int round_robin(Job * jobs, int n, int* arg_CPUs, int arg_num_CPU, long int global_start, pthread_mutex_t* arg_mutex,FILE* output){
  
  int next = 0, busy_CPUs = 0, i, next_stop = QUANTUM;
  
  rr_CPUs = arg_CPUs;
  rr_num_CPU = arg_num_CPU;
  rr_buffer = malloc(sizeof(Job*)*n);
  rr_running_jobs = malloc(sizeof(Job*)*rr_num_CPU);
  rr_threads = malloc(sizeof(pthread_t)*rr_num_CPU);
  rr_mutex = arg_mutex;
  rr_global_start = global_start;
  
  while(next < n || rr_buffer_size > 0){
    if(rr_buffer_size > 0 && time_diff(global_start) > next_stop){
      rr_reorder_jobs();
      next_stop += QUANTUM;
    }
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      if(get_debug()) fprintf(stderr,"O processo %s(linha: %d) chegou\n",*(&jobs[next].name),*(&jobs[next].line));
      rr_buffer[rr_buffer_size++] = &jobs[next++];
    }
    while((i = rr_get_next_free_CPU()) != -1 && rr_buffer_size > 0){
        rr_CPUs[i] = 1;
        rr_run_thread(rr_get_next_job(), i, output);
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < rr_num_CPU; i++)
      busy_CPUs += rr_CPUs[i];
  } while (busy_CPUs > 0);
  return 1;
}

Job* rr_get_next_job(){
  int i;
  Job* nextJob = rr_buffer[0];
  for(i = 1; i < rr_buffer_size; i++)
    rr_buffer[i-1] = rr_buffer[i];
  rr_buffer_size--;
  return nextJob;
}

int rr_compare_jobs_by_slack_time(const void * a, const void * b){
  Job* A = *(Job**)a;
  Job* B = *(Job**)b;
  return A->priority > B->priority;
}

void rr_run_thread(Job* job, int CPU_index, FILE* output){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  rr_running_jobs[CPU_index] = job;
  if(get_debug()) fprintf(stderr,"A cpu %d foi ocupada pelo processo %s\n", CPU_index, job->name);
  job->real_start = define_start();
  pthread_create(&rr_threads[CPU_index], NULL, simulate, (void *) args);
}

int rr_get_next_free_CPU(){
  int i;
  for (i = 0; i < rr_num_CPU; i++){
    if(!rr_CPUs[i]) {
      return i;
    }
  }
  return -1;
}

void rr_reorder_jobs(){
  int i;
  for(i = 0; i < rr_num_CPU; i++){
    pthread_mutex_lock(&rr_mutex[i]);
    if(rr_CPUs[i]){
      pthread_cancel(rr_threads[i]);
      rr_CPUs[i] = 0;
      if(get_debug()){
        fprintf(
          stderr, 
          "O processo %s deixou de usar a cpu %i\n", 
          rr_running_jobs[i]->name, 
          i
        );
      }
      rr_running_jobs[i]->duration -= time_diff(rr_running_jobs[i]->real_start)/1000.0;
      if(rr_running_jobs[i]->duration < 0.01){
        rr_running_jobs[i]->duration = 0.01;
      }
      rr_buffer[rr_buffer_size++] = rr_running_jobs[i];
    }
    pthread_mutex_unlock(&rr_mutex[i]);
  }
}

double rr_get_slack_time(Job* job){
  return job->deadline*1000 - (time_diff(rr_global_start) + job->duration*1000);
}
