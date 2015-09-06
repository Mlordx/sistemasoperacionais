#include <stdlib.h>
#include <stdio.h>
#include "scheduler.h"

int main (int argc, char* argv[]){
  FILE *fp = NULL;

  if(argc < 2){
    fprintf(stderr, "Número de argumentos insuficientes.\n");
    exit(-1);
  }

  if(argc == 3)
    fp = fopen(argv[2], "r");

  run_jobs(fp, atoi(argv[1]));
  if(fp != NULL)
    fclose(fp);
  return 0;
}