#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "time_handler.h"
#include "first_in_first_out.h"
#include "shortest_job_first.h"
#include "shortest_remaining_time_next.h"
#include "round_robin.h"
#include "real_time_least_slack_time.h"

double new_number(int);
int compare_jobs(const void *, const void *);
void print_jobs(Job*, int);
void run_thread(pthread_t, double, int);
void read_from_file(FILE* , Job* , int*);
void generate_randomly(Job* , int);
int pick_mode(int, Job*, int, int*, int, long int,FILE*);




int* CPUs;
long int global_start;
pthread_mutex_t* mutex;

void print_job(Job* job){
  printf("%s: %f\n", job->name, job->duration);
}

void* simulate(void *args){
  long int start = define_start();
  Data arguments = *(Data*) args;
  while(1){
    long unsigned int diff = time_diff(start);
    if(diff >= arguments.job->duration*1000) {
      usleep(1);
      pthread_mutex_lock(&mutex[arguments.cpu]);
      fprintf(
	      arguments.output, 
	      "%s %f %f\n", 
	      arguments.job->name, 
	      time_diff(global_start)/1000.0, 
	      time_diff(global_start)/1000.0 - arguments.job->arrival
	      );
      CPUs[arguments.cpu] = 0;
      pthread_mutex_unlock(&mutex[arguments.cpu]);
      break;
    }
  }
  return args;
}

int run_jobs(FILE* trace, int mode,FILE* output){
  int i, numCPU = sysconf( _SC_NPROCESSORS_ONLN )-1, n_jobs;
  Job processes[1000];

  CPUs = malloc(sizeof(int)*numCPU);
  for(i = 0; i < numCPU; i++)
    CPUs[i] = 0;
  
  mutex = malloc(sizeof(pthread_mutex_t)*numCPU);

  if(trace != NULL){
    read_from_file(trace, processes, &n_jobs);
  }
  else{
    n_jobs = 100;
    generate_randomly(processes, n_jobs);
  }

  qsort(processes, n_jobs, sizeof(Job), compare_jobs);
  global_start = define_start();
  pick_mode(mode, processes, n_jobs, CPUs, numCPU, global_start, output);
  return mode;
}

int pick_mode(int mode, Job* processes, int n_jobs, int* CPUs, int numCPU, long int global_start, FILE* output)
{
  switch(mode){
    case 1:
      return first_in_first_out(processes, n_jobs, CPUs, numCPU, global_start, output);
    case 2:
      return shortest_job_first(processes, n_jobs, CPUs, numCPU, global_start, output);
    case 3:
      return shortest_remaining_time_next(processes, n_jobs, CPUs, numCPU, global_start, mutex, output);
    case 4:
      return round_robin(processes, n_jobs, CPUs, numCPU, global_start, mutex, output);
    case 6:
      return real_time_least_slack_time(processes, n_jobs, CPUs, numCPU, global_start, mutex, output);
  }
  return -1;
}

void read_from_file(FILE* trace, Job* processes, int* n_jobs){
  int i = 0;
  float arrival, duration, deadline;
  char* name = malloc(sizeof(char)*20);

  while (fscanf(trace, "%f %s %f %f 0", &arrival, name, &duration, &deadline) != EOF) {
    processes[i].name = name;
    processes[i].arrival = arrival;
    processes[i].duration = duration;
    processes[i++].deadline = deadline;
    name = malloc(sizeof(char)*20);
  }

  *n_jobs = i;
}

void generate_randomly(Job* processes, int n_jobs){
  int i;
  srand(3);
  for(i = 0; i < n_jobs; i++){
    processes[i].name = malloc(sizeof(char)*20);
    processes[i].arrival = new_number(5);
    processes[i].duration = new_number(1);
    processes[i].deadline = new_number(15) + (int) processes[i].arrival + 1;
    sprintf(processes[i].name, "processo%d_%f", i, processes[i].deadline);
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
