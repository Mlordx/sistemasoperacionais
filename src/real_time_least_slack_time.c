#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "real_time_least_slack_time.h"

void rt_run_thread(Job*, int, FILE*);
Job* rt_get_next_job();
int rt_compare_jobs_by_slack_time(const void * a, const void * b);
int rt_get_next_free_CPU();
void rt_reorder_jobs();
double rt_get_slack_time(Job* job);

Job** rt_buffer;
int rt_buffer_size = 0;
Job** rt_running_jobs;
int* rt_CPUs;
int rt_num_CPU;
pthread_t* rt_threads = NULL;
pthread_mutex_t* rt_mutex = NULL;
long int rt_global_start;

int real_time_least_slack_time(Job * jobs, int n, int* arg_CPUs, int arg_num_CPU, long int global_start, pthread_mutex_t* arg_mutex,FILE* output){
  
  int next = 0, busy_CPUs = 0, i;
  
  rt_CPUs = arg_CPUs;
  rt_num_CPU = arg_num_CPU;
  rt_buffer = malloc(sizeof(Job*)*n);
  rt_running_jobs = malloc(sizeof(Job*)*rt_num_CPU);
  rt_threads = malloc(sizeof(pthread_t)*rt_num_CPU);
  rt_mutex = arg_mutex;
  rt_global_start = global_start;


  
  while(next < n || rt_buffer_size > 0){
    if(next < n && time_diff(global_start) >= jobs[next].arrival*1000){
      rt_buffer[rt_buffer_size++] = &jobs[next++];
      if(rt_get_next_free_CPU() == -1)
        rt_reorder_jobs();
    }
    while((i = rt_get_next_free_CPU()) != -1 && rt_buffer_size > 0){
        rt_CPUs[i] = 1;
        rt_run_thread(rt_get_next_job(), i, output);
    }
  }

  do{
    busy_CPUs = 0;
    for(i = 0; i < rt_num_CPU; i++)
      busy_CPUs += rt_CPUs[i];
  } while (busy_CPUs > 0);
  return 1;
}

Job* rt_get_next_job(){
  qsort(rt_buffer, rt_buffer_size, sizeof(Job*), rt_compare_jobs_by_slack_time);
  return rt_buffer[--rt_buffer_size];
}

int rt_compare_jobs_by_slack_time(const void * a, const void * b){
  Job* A = *(Job**)a;
  Job* B = *(Job**)b;
  return rt_get_slack_time(A) < rt_get_slack_time(B);
}

void rt_run_thread(Job* job, int CPU_index, FILE* output){  
  Data* args;
  args = malloc(sizeof(Data));
  args->job = job;
  args->cpu = CPU_index;
  args->output = output;
  rt_running_jobs[CPU_index] = job;
  job->real_start = define_start();
  pthread_create(&rt_threads[CPU_index], NULL, simulate, (void *) args);
}

int rt_get_next_free_CPU(){
  int i;
  for (i = 0; i < rt_num_CPU; i++){
    if(!rt_CPUs[i]) {
      return i;
    }
  }
  return -1;
}

void rt_reorder_jobs(){
  int i;

  for(i = 0; i < rt_num_CPU; i++){
    pthread_mutex_lock(&rt_mutex[i]);
    if(rt_CPUs[i]){
      pthread_cancel(rt_threads[i]);
      rt_CPUs[i] = 0;
      rt_running_jobs[i]->duration -= time_diff(rt_running_jobs[i]->real_start)/1000.0;
      if(rt_running_jobs[i]->duration < 0.01){
        rt_running_jobs[i]->duration = 0.01;
      }
      rt_buffer[rt_buffer_size++] = rt_running_jobs[i];
    }
    pthread_mutex_unlock(&rt_mutex[i]);
  }
}

double rt_get_slack_time(Job* job){
  return job->deadline*1000 - (time_diff(rt_global_start) + job->duration*1000);
}
