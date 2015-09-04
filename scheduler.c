#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "scheduler.h"

#define N_JOBS 20

double new_number(int);
int compare_jobs(const void *, const void *);
void print_jobs(Job*, int);

int simulate(void *duration){
  struct timeval stop, start;
  double duration_value = *(double *) duration;
  gettimeofday(&start, NULL);
  duration_value *= 1000;
  while(1){
    long unsigned int diff;
    gettimeofday(&stop, NULL);
    diff = (stop.tv_usec - start.tv_usec)/1000;
    if(diff > 1000) printf("ola\n");
    if(diff > duration_value) break;
  }
  return 1;
}

int first_in_first_out(Job * jobs, int n){
  int i;
  struct timeval now, start;
  
  qsort(jobs, n, sizeof(Job), compare_jobs);  
  gettimeofday(&start, NULL);
  for(i = 0; i < n; i++){
    int job_arrival = jobs[i].arrival*1000000;
    gettimeofday(&now, NULL);
    if((now.tv_usec - start.tv_usec) < job_arrival)
      usleep((int) (job_arrival - (now.tv_usec - start.tv_usec)));
    printf("Processo %d comecou a rodar depois de %ld microsegundos\n", i, (now.tv_usec - start.tv_usec));
    printf("%ld, %ld\n",start.tv_usec, now.tv_usec);
    simulate(&jobs[i].duration);
  }
  return 1;
}

int run_jobs(FILE* trace, int mode){
  int i;
  Job processes[20];
  
  srand(1);
  for(i = 0; i < N_JOBS; i++){
    processes[i].arrival = new_number(5);
    processes[i].duration = new_number(1);
  }
  /* jobs* processes = parse(trace);*/
  first_in_first_out(processes, N_JOBS);
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
    printf("%d: %f\n", i, jobs[i].arrival);
  }
}