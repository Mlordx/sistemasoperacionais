#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "first_in_first_out.h"
#include "shortest_job_first.h"
#include "scheduler.h"

double new_number(int);
int compare_jobs(const void *, const void *);
void print_jobs(Job*, int);
void run_thread(pthread_t, double, int);
void read_from_file(FILE* trace, Job* processes, int* n_jobs);
void generate_randomly(Job* processes, int n_jobs);
int pick_mode(int, Job*, int, int*, int, long int);

int* CPUs;
long int global_start;

void* simulate(void *args){
  long int start = define_start();
  Data arguments = *(Data*) args;
  while(1){
    long unsigned int diff = time_diff(start);
    if(diff > arguments.job.duration*1000) {
      printf( 
        "%s %f %f\n", 
        arguments.job.name, 
        time_diff(global_start)/1000.0, 
        time_diff(global_start)/1000.0 - arguments.job.arrival
      );
      break;
    }
  }
  CPUs[arguments.cpu] = 0;
  return args;
}

int run_jobs(FILE* trace, int mode){
  int i, numCPU = sysconf( _SC_NPROCESSORS_ONLN )-1, n_jobs;
  Job processes[100];
  
  CPUs = malloc(sizeof(int)*numCPU);
  for(i = 0; i < numCPU; i++)
    CPUs[i] = 0;
  
  if(trace != NULL){
    read_from_file(trace, processes, &n_jobs);
  }
  else{
    n_jobs = 100;
    generate_randomly(processes, n_jobs);
  }

  qsort(processes, n_jobs, sizeof(Job), compare_jobs);
  global_start = define_start();
  pick_mode(mode, processes, n_jobs, CPUs, numCPU, global_start);
  return mode;
}

int pick_mode(int mode, Job* processes, int n_jobs, int* CPUs, int numCPU, long int global_start)
{
  switch(mode){
    case 1: return first_in_first_out(processes, n_jobs, CPUs, numCPU, global_start);
    case 2: return shortest_job_first(processes, n_jobs, CPUs, numCPU, global_start);
  }
  return -1;
}

void read_from_file(FILE* trace, Job* processes, int* n_jobs){
  int i = 0;
  float arrival, duration;
  char* name = malloc(sizeof(char)*20);

  while (fscanf(trace, "%f %s %f 0 0", &arrival, name, &duration) != EOF) {
    printf("teste\n");
    processes[i].name = name;
    processes[i].arrival = arrival;
    processes[i++].duration = duration;
    printf("%f %s %f 0 0\n", processes[i-1].arrival, processes[i-1].name, processes[i-1].duration);
    name = malloc(sizeof(char)*20);
  }

  *n_jobs = i;
}

void generate_randomly(Job* processes, int n_jobs){
  int i;
  srand(2);
  for(i = 0; i < n_jobs; i++){
    processes[i].name = malloc(sizeof(char)*20);
    sprintf(processes[i].name, "processo%d", i);
    processes[i].arrival = new_number(5);
    processes[i].duration = new_number(1);
  }
}

double new_number(int max){
  return 1.0*rand()/RAND_MAX*max;
}

int compare_jobs(const void * a, const void * b){
  Job A = *(Job*)a;
  Job B = *(Job*)b;
  return A.arrival > B.arrival;
}

void print_jobs(Job* jobs, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%s: %f\n", jobs[i].name, jobs[i].arrival);
  }
}