#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "scheduler.h"

#define N_JOBS 20

double new_number(int);
int compare_jobs(const void *, const void *);
void print_jobs(Job*, int);
long int time_diff(struct timeval, struct timeval);
long int get_miliseconds(struct timeval);
void run_thread(pthread_t, double, int);

typedef struct data{
    int cpu;
    double duration;
} Data;

int* CPUs;

void* simulate(void *args){
  struct timeval stop, start;
  Data arguments = *(Data*) args;
  gettimeofday(&start, NULL);
  while(1){
    long unsigned int diff;
    gettimeofday(&stop, NULL);
    diff = time_diff(start, stop);
    
    if(diff > arguments.duration) {
      printf("Essa thread durou %ld milisegundos no cpu %d\n", diff, arguments.cpu);
      break;
    }
  }
  CPUs[arguments.cpu] = 0;
  return args;
}

int first_in_first_out(Job * jobs, int n){
  int i = 0;
  int next = 0;
  struct timeval now, start;
  int numCPU = sysconf( _SC_NPROCESSORS_ONLN )-1;
  pthread_t* threads = malloc(sizeof(pthread_t)*n);
  int CPU_ocupados;
  
  CPUs = malloc(sizeof(int)*numCPU);
  for(i = 0; i < numCPU; i++)
    CPUs[i] = 0;

  qsort(jobs, n, sizeof(Job), compare_jobs);  
  gettimeofday(&start, NULL);
  
  while(next < n){
    for(i = 0; i < numCPU; i++){
      if(!CPUs[i]){
        gettimeofday(&now, NULL);
        if(time_diff(start, now) > jobs[next].arrival*1000){
            printf ("Thread %d chegou em %f  milisegundos e foi lancada em %ld milisegundos no cpu %d\n", next, jobs[next].arrival*1000, time_diff(start, now), i);
          run_thread(threads[next], jobs[next].duration, i);
          next++;
        }
      }
    }
  }

  do{
    CPU_ocupados = 0;
    for(i = 0; i < numCPU; i++)
      CPU_ocupados += CPUs[i];
  } while (CPU_ocupados > 0);

  /*for(i = 0; i < n; i++){
    int job_arrival = jobs[i].arrival*1000000;
    gettimeofday(&now, NULL);
    if(time_diff(start, now) < job_arrival)
      usleep((int) (job_arrival - time_diff(start, now)));
    printf("Processo %d comecou a rodar depois de %ld microsegundos\n", i, time_diff(start, now));
    simulate(&jobs[i].duration);
  }*/
  return 1;
}

void run_thread(pthread_t thread, double duration, int CPU_index){  
  Data* args;
  args = malloc(sizeof(Data));
  args->duration = duration*1000;
  args->cpu = CPU_index;
  CPUs[CPU_index] = 1;
  pthread_create(&thread, NULL, simulate, (void *) args);
}

int run_jobs(FILE* trace, int mode){
  int i;
  Job processes[20];
  
  srand(2);
  for(i = 0; i < N_JOBS; i++){
    processes[i].arrival = new_number(5);
    processes[i].duration = new_number(5);
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

long int time_diff(struct timeval begin, struct timeval end){
  long int begin_mili = get_miliseconds(begin);
  long int end_mili = get_miliseconds(end);
  return end_mili - begin_mili;
}

long int get_miliseconds(struct timeval t){
  return t.tv_sec*1000 + t.tv_usec/1000;
}