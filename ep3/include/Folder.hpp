#ifndef HPP_FOLDER_DEFINED
#define HPP_FOLDER_DEFINED

//Standard Libraries
#include <string>
#include <memory>
#include <vector>

// EP3 Classes
#include "FileEntry.hpp"

class Folder : public FileEntry, public std::enable_shared_from_this<FileEntry>{
 private:
  std::vector<std::shared_ptr<FileEntry> > files_;
 public: 
  Folder(std::string name);
  Folder(std::string name, std::shared_ptr<FileEntry>);
  void addFile(std::shared_ptr<FileEntry>);
  void addParent(std::shared_ptr<FileEntry>);
  std::vector<std::shared_ptr<FileEntry> >& getFiles();
  std::string getData();

};

#endif
