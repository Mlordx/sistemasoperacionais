#include <string.h>
#include "parser_shell.h"


int verifica_cd(char command[]){
  char command_copy[MAX_COMMAND_SIZE];
  char* tokens;

  strcpy(command_copy, command);
  tokens = strtok(command_copy," ");

  return strcmp(tokens, "cd") == 0;
}

int verifica_executavel(char command[]){
  char command_copy[MAX_COMMAND_SIZE];
  char* tokens;

  strcpy(command_copy, command);
  tokens = strtok(command_copy," ");
  
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
