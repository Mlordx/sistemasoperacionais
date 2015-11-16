//Standard Libraries
#include <iostream>
#include <sstream>
#include <vector>

// Interface
#include "Terminal.hpp"

// EP3 Classes
#include "FileSystem.hpp"
#include "FileEntry.hpp"
#include "Folder.hpp"
#include "LeaveCommand.hpp"


using namespace std;

vector<string> &split(const string &input, char delim, vector<string> &args) {
  stringstream stream(input);
  string item;
  while (getline(stream, item, delim)) 
    if(item != "")
      args.push_back(item);
  return args;
}

Terminal::Terminal(){
  shared_ptr<Command> sai(new LeaveCommand);
  FileSystem teste;
  teste.init("fs.txt");
  commands_["sai"] = sai;
}

void Terminal::run(char* input){
  string sInput(input);
  vector<string> args;
  split(sInput, ' ', args);
  string command = args[0];
  args.erase(args.begin());

  if ( commands_.find(command) == commands_.end() ) {
    cout << "comando: '" << command <<"' não implementado\n";
  } else {
    commands_[command]->execute(args);
  }
}