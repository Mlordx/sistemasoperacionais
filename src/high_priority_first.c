#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "real_time_least_slack_time.h"

void hpf_run_thread(Job*, int, FILE*);
Job* hpf_get_next_job();
int hpf_compare_jobs_by_slack_time(const void * a, const void * b);
int hpf_get_next_free_CPU();
void hpf_reorder_jobs();
double hpf_get_slack_time(Job* job);

Job** hpf_buffer;
int hpf_buffer_size = 0;
Job** hpf_running_jobs;
int* hpf_CPUs;
int hpf_num_CPU;
pthread_t* hpf_threads = NULL;
pthread_mutex_t* hpf_mutex = NULL;
long int hpf_global_start;

int high_priority_first(Job * jobs, int n, int* arg_CPUs, int arg_num_CPU, long int global_start, pthread_mutex_t* arg_mutex,FILE* output){
  
  int next = 0, busy_CPUs = 0, i;
  
  hpf_CPUs = arg_CPUs;
  hpf_num_CPU = arg_num_CPU;
  hpf_buffer = malloc(sizeof(Job*)*n);
  hpf_running_jobs = malloc(sizeof(Job*)*hpf_num_CPU);
  hpf_threads = malloc(sizeof(pthread_t)*hpf_num_CPU);
  hpf_mutex = arg_mutex;
  hpf_global_start = global_start;
  
  while(next < n || hpf_buffer_size > 0){
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      if(get_debug()) fprintf(stderr,"O processo %s(linha: %d) chegou\n",*(&jobs[next].name),*(&jobs[next].line));
      hpf_buffer[hpf_buffer_size++] = &jobs[next++];
      if(hpf_get_next_free_CPU() == -1)
        hpf_reorder_jobs();
    }
    while((i = hpf_get_next_free_CPU()) != -1 && hpf_buffer_size > 0){
        hpf_CPUs[i] = 1;
        hpf_run_thread(hpf_get_next_job(), i, output);
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < hpf_num_CPU; i++)
      busy_CPUs += hpf_CPUs[i];
  } while (busy_CPUs > 0);
  return 1;
}

Job* hpf_get_next_job(){
  qsort(hpf_buffer, hpf_buffer_size, sizeof(Job*), hpf_compare_jobs_by_slack_time);
  return hpf_buffer[--hpf_buffer_size];
}

int hpf_compare_jobs_by_slack_time(const void * a, const void * b){
  Job* A = *(Job**)a;
  Job* B = *(Job**)b;
  return A->priority > B->priority;
}

void hpf_run_thread(Job* job, int CPU_index, FILE* output){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  hpf_running_jobs[CPU_index] = job;
  if(get_debug()) fprintf(stderr,"A cpu %d foi ocupada pelo processo %s\n", CPU_index, job->name);
  job->real_start = define_start();
  pthread_create(&hpf_threads[CPU_index], NULL, simulate, (void *) args);
}

int hpf_get_next_free_CPU(){
  int i;
  for (i = 0; i < hpf_num_CPU; i++){
    if(!hpf_CPUs[i]) {
      return i;
    }
  }
  return -1;
}

void hpf_reorder_jobs(){
  int i;

  for(i = 0; i < hpf_num_CPU; i++){
    pthread_mutex_lock(&hpf_mutex[i]);
    if(hpf_CPUs[i]){
      pthread_cancel(hpf_threads[i]);
      hpf_CPUs[i] = 0;
      if(get_debug()){
        fprintf(
          stderr, 
          "O processo %s deixou de usar a cpu %i\n", 
          hpf_running_jobs[i]->name, 
          i
        );
      }
      hpf_running_jobs[i]->duration -= time_diff(hpf_running_jobs[i]->real_start)/1000.0;
      if(hpf_running_jobs[i]->duration < 0.01){
        hpf_running_jobs[i]->duration = 0.01;
      }
      hpf_buffer[hpf_buffer_size++] = hpf_running_jobs[i];
    }
    pthread_mutex_unlock(&hpf_mutex[i]);
  }
}

double hpf_get_slack_time(Job* job){
  return job->deadline*1000 - (time_diff(hpf_global_start) + job->duration*1000);
}
