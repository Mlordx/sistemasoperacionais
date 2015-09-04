#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct job {
  double arrival, duration, deadline;
  char * name;
  int priority;
} Job;

int first_in_first_out(Job *, int);
int run_jobs(FILE* , int);

#endif
