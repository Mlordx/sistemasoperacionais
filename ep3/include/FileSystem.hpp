#ifndef HPP_FILESYSTEM_DEFINED
#define HPP_FILESYSTEM_DEFINED

#define BITMAP_BLOCKS 1
#define FILEMAP_BLOCKS 32
#define FILE_BLOCKS 25567

#define N_BLOCKS (BITMAP_BLOCKS + FILEMAP_BLOCKS + FILE_BLOCKS)
#define BLOCK_SIZE (4<<10)
#define TOTAL_SIZE (BLOCK_SIZE * N_BLOCKS - 1)
#define BITMAP_POSITION (TOTAL_SIZE - BITMAP_BLOCKS * BLOCK_SIZE)
#define FILEMAP_POSITION (BITMAP_POSITION - FILEMAP_BLOCKS * BLOCK_SIZE)

#include <fstream>

class FileSystem
{
 private:
  std::fstream disk_;

  void formatDisk();
 public:
  void init(std::string);
};

#endif