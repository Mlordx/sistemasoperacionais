#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include <pthread.h>
#include "scheduler.h"

int round_robin(Job *, int, int*, int, long int, pthread_mutex_t*);

#endif
