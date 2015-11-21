#ifndef HPP_FILESYSTEM_DEFINED
#define HPP_FILESYSTEM_DEFINED

#define BITMAP_BLOCKS 1
#define FILEMAP_BLOCKS 38
#define FILE_BLOCKS 25561

#define N_BLOCKS (BITMAP_BLOCKS + FILEMAP_BLOCKS + FILE_BLOCKS)
#define BLOCK_SIZE (4<<10)
#define TOTAL_SIZE (BLOCK_SIZE * N_BLOCKS)
#define BITMAP_POSITION (TOTAL_SIZE - BITMAP_BLOCKS * BLOCK_SIZE)
#define FILEMAP_POSITION (BITMAP_POSITION - FILEMAP_BLOCKS * BLOCK_SIZE)

//Standard Libraries
#include <fstream>
#include <memory>
#include <sstream>

//EP3 Libraries
#include "FileEntry.hpp"
#include "Folder.hpp"

class FileSystem : public std::enable_shared_from_this<FileSystem>{
 private:
  std::fstream disk_;
  std::shared_ptr<Folder> currentFolder_;
  std::vector<int> fileMap_;

  void formatDisk();
  std::vector<std::string> getFileChunks(std::string);
  void addMapRegistry(int, int);
  std::shared_ptr<Folder> getInitialFolder(std::string& path);
  void initFileMap();
  int getTotalSize(std::shared_ptr<Folder>, int*, int*);
  int getTotalEmptySpace();
  
 public:
  FileSystem() = default;
  void init(std::string);
  bool isDisk(std::string fileName);
  bool isOpen();
  void persist(std::shared_ptr<FileEntry> entry);
  void removeFile(int block);
  void removeFolder(std::shared_ptr<Folder> folder);
  void setCurrentFolder(std::shared_ptr<Folder> f);
  std::shared_ptr<Folder> getCurrentFolder();
  void close();
  void printInfo();
  int getNextFreeBlock();
  std::string getFileData(int);
  std::shared_ptr<Folder> getPathFolder(std::string&);  
  std::shared_ptr<Folder> loadFolder(int block);
};

#endif
