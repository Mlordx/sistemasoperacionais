#ifndef PAGE_ALGORITHM_HPP
#define PAGE_ALGORITHM_HPP

#include <vector>
#include "memory.hpp"

class PageAlgorithm: public std::enable_shared_from_this<PageAlgorithm>{
public:
  virtual int readPage(std::vector<Page>, int) =0;
};

#endif // PAGE_ALGORITHM_HPP
