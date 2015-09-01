#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "string.h"

int main(){
  char* input, shell_prompt[100];
  rl_bind_key('\t', rl_complete);
  
  while(1){
    snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
    
    input = readline(shell_prompt);

    if (!input)
      break;

    add_history(input);


    free(input);  

     
  }

  
  return 0;

}
