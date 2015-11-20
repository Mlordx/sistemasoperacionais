#ifndef HPP_FILEENTRY_DEFINED
#define HPP_FILEENTRY_DEFINED

// C Libraries
#include <time.h>

//Standard Libraries
#include <string>
#include <vector>

class FileEntry{
 private:
  std::string data_;
  std::string name_;
  int size_;
  time_t creationTime_;
  time_t modificationTime_;
  time_t accessTime_;
  int initialBlock_;

 public:

  FileEntry(std::string fileName);

  virtual std::string getData();
  virtual bool isFolder();
  
  std::string getName();
  int getSize();
  time_t getCreationTime();
  time_t getModificationTime();
  time_t getAccessTime();
  int getInitialBlock();
  void printFormattedInfo();

  void initFromData(std::vector<std::string>);

  void setData(std::string);
  void setName(std::string);
  void setSize(int);
  void setCreationTime();
  void setModificationTime();
  void setAccessTime();
  void setInitialBlock(int);

};

#endif