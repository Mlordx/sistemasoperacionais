#ifndef HPP_FILEENTRY_DEFINED
#define HPP_FILEENTRY_DEFINED

// C Libraries
#include <time.h>

//Standard Libraries
#include <string>

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
  void setData(std::string);
  
  std::string getName();
  int getSize();
  time_t getCreationTime();
  time_t getModificationTime();
  time_t getAccessTime();
  int getInitialBlock();

  void setName(std::string);
  void setSize(int);
  void setCreationTime();
  void setModificationTime();
  void setAccessTime();
  void setInitialBlock(int);
};

#endif
