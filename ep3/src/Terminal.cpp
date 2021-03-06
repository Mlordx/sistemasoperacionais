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
#include "TouchCommand.hpp"
#include "MountCommand.hpp"
#include "UnmountCommand.hpp"
#include "CopyCommand.hpp"
#include "PrintCommand.hpp"
#include "MakeFolderCommand.hpp"
#include "ListCommand.hpp"
#include "StatusCommand.hpp"
#include "FindCommand.hpp"
#include "RemoveCommand.hpp"
#include "RemoveDirCommand.hpp"

using namespace std;

vector<string>& breakString(const string &input, char delim, vector<string> &args) {
  stringstream stream(input);
  string item;
  
  while (getline(stream, item, delim)) 
    if(item != "") args.push_back(item);
  
  return args;
}

Terminal::Terminal(){
  auto filesys = make_shared<FileSystem>();
  
  shared_ptr<Command> sai(new LeaveCommand);
  shared_ptr<Command> mount(new MountCommand(filesys));
  shared_ptr<Command> unmount(new UnmountCommand(filesys));
  shared_ptr<Command> touch(new TouchCommand(filesys));
  shared_ptr<Command> copy(new CopyCommand(filesys));
  shared_ptr<Command> print(new PrintCommand(filesys));
  shared_ptr<Command> mkdir(new MakeFolderCommand(filesys));
  shared_ptr<Command> list(new ListCommand(filesys));
  shared_ptr<Command> status(new StatusCommand(filesys));
  shared_ptr<Command> find(new FindCommand(filesys));
  shared_ptr<Command> removeFile(new RemoveCommand(filesys));
  shared_ptr<Command> removeFolder(new RemoveDirCommand(filesys));
  
  commands_["sai"] = sai;
  commands_["mount"] = mount;
  commands_["umount"] = unmount;
  commands_["touch"] = touch;
  commands_["cp"] = copy;
  commands_["cat"] = print;
  commands_["mkdir"] = mkdir;
  commands_["ls"] = list;
  commands_["df"] = status;
  commands_["find"] = find;
  commands_["rm"] = removeFile;
  commands_["rmdir"] = removeFolder;
}

void Terminal::run(char* input){
  string sInput(input);
  vector<string> args;
  breakString(sInput, ' ', args);

  if(args.empty())
    return;
  
  string command = args[0];
  args.erase(args.begin());

  if( commands_.find(command) == commands_.end() ){
    cout << "comando: '" << command <<"' não implementado\n";
  } else{
    commands_[command]->execute(args);
  }
}
