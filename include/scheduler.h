#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct job {
  double arrival, duration, deadline;
  char* name;
  int priority;
  long int real_start ;
} Job;

typedef struct data{
    int cpu;
    Job* job;
} Data;

void* simulate(void *);
int run_jobs(FILE* , int);

#endif
