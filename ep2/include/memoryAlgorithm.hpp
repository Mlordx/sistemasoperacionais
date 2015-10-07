#ifndef MEMORY_ALGORITHM_HPP
#define MEMORY_ALGORITHM_HPP

#include <string>
#include <memory>
#include "job.hpp"
#include "memory.hpp"

class MemoryAlgorithm{
protected:
  std::shared_ptr<MemorySlot> head_;
public:
  MemoryAlgorithm(std::shared_ptr<MemorySlot>);
  std::shared_ptr<MemorySlot> insertJob(Job, std::shared_ptr<MemorySlot>);
  virtual int execute(Job) =0;
};

#endif // MEMORY_ALGORITHM_HPP
