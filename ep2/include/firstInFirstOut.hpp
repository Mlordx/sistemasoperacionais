#ifndef FIRST_IN_FIRSTOUT_HPP
#define FIRST_IN_FIRSTOUT_HPP

#include <vector>

#include "memory.hpp"
#include "pageAlgorithm.hpp"

class FirstInFirstOut : public PageAlgorithm {
public:
  int readPage(std::vector<Page>&, int);
};

#endif // FIRST_IN_FIRSTOUT_HPP