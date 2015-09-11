#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct job {
  double arrival, duration, deadline;
  char* name;
  int priority, line;
  long int real_start;
} Job;

typedef struct data{
  int cpu;
  Job* job;
  FILE* output;
} Data;


void* simulate(void *);
int run_jobs(FILE* , int, FILE*);
void print_job(Job*);
int get_debug();
void set_debug();
int get_context();
void add_context();


#endif
