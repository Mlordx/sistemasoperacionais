#include "parser.h"
#include "string.h"

int verifica_cd(char command[]){
  char* tokens = strtok(command," ");
  return strcmp(tokens, "cd") == 0;
}

int verifica_executavel(char command[]){
  char* tokens = strtok(command," ");
  return tokens[0] == '/' || (tokens[0] == '.' && tokens[1] == '/');
}

int parse(char command[]){
  if(strcmp(command, "pwd") == 0)
    return PWD;
  if(verifica_cd(command))
    return CD;
  if(verifica_executavel(command))
    return EXECUTE;
  return IGNORE;
}
