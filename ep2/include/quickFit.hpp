#ifndef QUICK_FIT_HPP
#define QUICK_FIT_HPP


#include <memory>

#include <memoryAlgorithm.hpp>
#include <job.hpp>
#include <memory.hpp>

class QuickFit : public MemoryAlgorithm{
private:
  std::shared_ptr<MemorySlot> head_;
  std::vector< std::vector< std::shared_ptr<MemorySlot> > > memory_list;
public:
  QuickFit(std::shared_ptr<MemorySlot>);
  void updateMemoryList(std::shared_ptr<MemorySlot>);
  int execute(Job);
};
  
#endif // QUICK_FIT_HPP
