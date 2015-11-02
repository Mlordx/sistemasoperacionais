// Standard Libraries
#include <iostream>

// Interface
#include "LeaveCommand.hpp"

using namespace std;

int LeaveCommand::execute(vector<string> args){
  cout << "Saindo..." << endl;
  exit(1);
}
