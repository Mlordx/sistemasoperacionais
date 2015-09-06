#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "shell.h"

int main(){
  char* input, shell_prompt[100], *dir = NULL;
  rl_bind_key('\t', rl_complete);

  while(1){
    snprintf(shell_prompt, sizeof(shell_prompt), "%s $ ", getcwd(dir, 1024));
    free(dir);
    
    input = readline(shell_prompt);

    if (!input)
      break;

    add_history(input);
    run(input);

    free(input);  

     
  }

  
  return 0;

}
