/************************
EP2 - SO
Vinícius Silva - 7557626
Mateus Barros - 7991037

*************************/

#ifndef MEMORY_ALGORITHM_HPP
#define MEMORY_ALGORITHM_HPP

#include <string>
#include <memory>
#include "job.hpp"
#include "memory.hpp"

class MemoryAlgorithm: public std::enable_shared_from_this<MemoryAlgorithm>{
protected:
  std::shared_ptr<MemorySlot> head_;
public:
  MemoryAlgorithm(std::shared_ptr<MemorySlot>);
  std::shared_ptr<MemorySlot> insertJob(Job, std::shared_ptr<MemorySlot>);
  int getRealSize(Job);
  virtual int execute(Job) =0;
};

#endif // MEMORY_ALGORITHM_HPP
