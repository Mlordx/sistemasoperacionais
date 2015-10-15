#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <vector>

#include "job.hpp"
#include "memoryManager.hpp"

class Simulator{
private:
  std::vector<Job> running_;
  bool insert(std::shared_ptr<MemoryManager>, std::vector<Job>&, int);
  bool read(std::shared_ptr<MemoryManager>, std::vector<Job>&, int);
  bool remove(std::shared_ptr<MemoryManager>, std::vector<Job>&, int);
public:
  void run(std::vector<Job>&, std::shared_ptr<MemoryManager>, int);
};

#endif // SIMULATOR_HPP
