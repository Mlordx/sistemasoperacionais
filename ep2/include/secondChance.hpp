#ifndef SECOND_CHANCE_HPP
#define SECOND_CHANCE_HPP

#include <vector>

#include "memory.hpp"
#include "pageAlgorithm.hpp"

class SecondChance : public PageAlgorithm {
public:
  int readPage(std::vector<Page>&, int);
};

#endif // SECOND_CHANCE_HPP