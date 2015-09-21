#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser_shell.h"
#include "shell.h"

char** get_arguments(char * command){
  char** arguments;
  int i;
  arguments = malloc(sizeof (char*)*100);
  arguments[0] = strtok(command, " ");
  
  for(i = 1; arguments[i-1] != NULL; i++)
    arguments[i] = strtok(NULL, " ");
  
  return arguments;
}

int pwd(){
  char * dir = NULL;
  printf("%s\n", getcwd(dir, 1024));
  free(dir);
  return 1;
}

int cd(char * command){
  strtok(command, " ");
  chdir(strtok(NULL, " "));
  return 1;
}

int execute(char * command){
  pid_t pid;
  int status;
  char *envp[] = { NULL };
  char ** argv = get_arguments(command);
  
  switch ( pid = fork() ) {
    case -1:
      perror("Erro ao criar novo processo");
      free(argv);
      return 0;
    case 0: 
      status = execve(argv[0], argv, envp);
      exit(status);
    default:
      free(argv);
      if( waitpid(pid, &status, 0) < 0 ) {
	perror("Não conseguiu recuperar o processo filho");
	exit(EXIT_FAILURE);
      }
 
      if( WIFEXITED(status) ) {
	return WEXITSTATUS(status);
      }
      return 0;
  }
}

int run (char * command){
  switch(parse(command)){
    case PWD:
      return pwd();
    case CD:
      return cd(command);
    case EXECUTE:
      return execute(command);
    default:
      return 1;
  }
}

