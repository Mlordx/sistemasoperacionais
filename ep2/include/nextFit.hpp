/************************
EP2 - SO
Vinícius Silva - 7557626
Mateus Barros - 7991037

*************************/

#ifndef NEXT_FIT_HPP
#define NEXT_FIT_HPP

#include <string>
#include <memory>
#include "memoryAlgorithm.hpp"
#include "job.hpp"
#include "memory.hpp"

class NextFit : public MemoryAlgorithm{
private:
  std::shared_ptr<MemorySlot> next_;
public:
  NextFit(std::shared_ptr<MemorySlot>);
  int execute(Job);
};

#endif // NEXT_FIT_HPP
