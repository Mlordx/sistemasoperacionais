#ifndef FIRSTFIT_HPP
#define FIRSTFIT_HPP

#include <vector>
#include <memory>

#include <memory.hpp>
#include <memoryAlgorithm.hpp>

#include <job.hpp>

class FirstFit : public MemoryAlgorithm{
protected:
  std::shared_ptr<MemorySlot> list;
public:
  FirstFit(std::shared_ptr<MemorySlot>);
  int execute(Job);
};

#endif // FIRSTFIT_HPP
