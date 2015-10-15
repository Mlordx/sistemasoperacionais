#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>

#include "job.hpp"
#include "memoryManager.hpp"

class Simulator{
private:
  std::vector<Job> running_;
  bool insert(MemoryManager*, std::vector<Job>&, int);
  bool read(MemoryManager*, std::vector<Job>&, int);
  bool remove(MemoryManager*, std::vector<Job>&, int);
public:
  void run(std::vector<Job>&, MemoryManager*, int);
};

#endif // SIMULATOR_HPP
