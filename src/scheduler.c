#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "first_in_first_out.h"
#include "scheduler.h"

#define N_JOBS 20

double new_number(int);
int compare_jobs(const void *, const void *);
void print_jobs(Job*, int);
void run_thread(pthread_t, double, int);

int* CPUs;
long int global_start;

void* simulate(void *args){
  long int start = define_start();
  Data arguments = *(Data*) args;
  while(1){
    long unsigned int diff = time_diff(start);
    if(diff > arguments.job.duration*1000) {
      printf( 
        "%s %ld %ld\n", 
        arguments.job.name, 
        time_diff(global_start), 
        time_diff(global_start) - (long int) (arguments.job.arrival*1000)
      );
      break;
    }
  }
  CPUs[arguments.cpu] = 0;
  return args;
}

int run_jobs(FILE* trace, int mode){
  int i;
  Job processes[20];
  int numCPU = sysconf( _SC_NPROCESSORS_ONLN )-1;
  
  CPUs = malloc(sizeof(int)*numCPU);
  for(i = 0; i < numCPU; i++)
    CPUs[i] = 0;
  
  srand(2);
  for(i = 0; i < N_JOBS; i++){
    sprintf(processes[i].name, "processo%d", i);
    processes[i].arrival = new_number(5);
    processes[i].duration = new_number(5);
  }
  qsort(processes, N_JOBS, sizeof(Job), compare_jobs);
  global_start = define_start();
  first_in_first_out(processes, N_JOBS, CPUs, numCPU, global_start);
  return mode;
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