#include <sys/time.h>
#include <stdlib.h>

long int get_miliseconds(struct timeval );

long int define_start(){
  struct timeval start;
  gettimeofday(&start, NULL);
  return get_miliseconds(start);
}

long int time_diff(long int start){
  struct timeval now;
  long int end;
  gettimeofday(&now, NULL);
  end = get_miliseconds(now);
  return end - start;
}

long int get_miliseconds(struct timeval t){
  return t.tv_sec*1000 + t.tv_usec/1000;
}
