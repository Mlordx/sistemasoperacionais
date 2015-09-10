#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

int main (int argc, char* argv[]){
  FILE* output;
  FILE *fp = NULL;

  if(argc < 4){
    fprintf(stderr, "Número de argumentos insuficientes.\n");
    exit(-1);
  }

  fp = fopen(argv[2], "r");
  output = fopen(argv[3], "w");
  
  run_jobs(fp, atoi(argv[1]),output);
  
  if(fp != NULL) fclose(fp);
  
  return 0;
}
