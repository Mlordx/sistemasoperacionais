#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduler.h"

int main (int argc, char* argv[]){
  FILE* output = NULL;
  FILE *fp = NULL;

  if(argc < 4){
    fprintf(stderr, "Número de argumentos insuficientes.\n");
    exit(-1);
  }

  fp = fopen(argv[2], "r");    
  output = fopen(argv[3], "w");

  if(argv[4] != NULL && *(argv[4]) == 'd')set_debug();
  
  run_jobs(fp, atoi(argv[1]),output);

  if(get_debug()) fprintf(stderr,"%d\n",get_context());

  if(fp != NULL) fclose(fp);
  fclose(output);
  
  return 0;
}
