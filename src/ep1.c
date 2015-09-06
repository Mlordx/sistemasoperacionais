#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

int main (int argc, char* argv[]){
  FILE *fp;

  if(argc < 3){
    fprintf(stderr, "Número de argumentos insuficientes.\n");
    exit(-1);
  }

  fp = fopen(argv[2], "r");
  run_jobs(fp, atoi(argv[1]));
  fclose(fp);

  return 0;
}