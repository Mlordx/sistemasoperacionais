//Standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

//Readline
#include <readline/readline.h>
#include <readline/history.h>

//EP3 Classes
#include "Terminal.hpp"

int main(){
  char* input, shell_prompt[100], *dir = NULL;
  rl_bind_key('\t', rl_complete);
  Terminal terminal;

  while(1){
    snprintf(shell_prompt, sizeof(shell_prompt), "$ ");
    free(dir);
    
    input = readline(shell_prompt);

    if (!input){
      std::cout << std::endl;
      break;
    }

    terminal.run(input);

    add_history(input);
    free(input);
  }
  
  return 0;
}
