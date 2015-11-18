#ifndef HPP_FILESYSTEM_DEFINED
#define HPP_FILESYSTEM_DEFINED

#define BITMAP_BLOCKS 1
#define FILEMAP_BLOCKS 1
#define FILE_BLOCKS 10

#define N_BLOCKS (BITMAP_BLOCKS + FILEMAP_BLOCKS + FILE_BLOCKS)
#define BLOCK_SIZE (4<<10)
#define TOTAL_SIZE (BLOCK_SIZE * N_BLOCKS - 1)
#define BITMAP_POSITION (TOTAL_SIZE - BITMAP_BLOCKS * BLOCK_SIZE)
#define FILEMAP_POSITION (BITMAP_POSITION - FILEMAP_BLOCKS * BLOCK_SIZE)

//Standard Libraries
#include <fstream>
#include <memory>

//EP3 Libraries
#include "FileEntry.hpp"
#include "Folder.hpp"

class FileSystem : public std::enable_shared_from_this<FileSystem>{
 private:
  std::fstream disk_;
  std::shared_ptr<Folder> currentFolder_;
  std::vector<int> fileMap_;
  void formatDisk();
  
 public:
  FileSystem() = default;
  void init(std::string);
  bool isDisk(std::string fileName);
  void persist(std::shared_ptr<FileEntry> entry, int block);
  void setCurrentFolder(std::shared_ptr<Folder> f);
  std::shared_ptr<Folder> getCurrentFolder();
  std::vector<int> getFileMap();
};

#endif
