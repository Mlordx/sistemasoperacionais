#ifndef PAGE_ALGORITHM_HPP
#define PAGE_ALGORITHM_HPP

#include <vector>
#include "memoryManager.hpp"

class PageAlgorithm: public std::enable_shared_from_this<PageAlgorithm>{
public:
  //virtual int execute(std::vector<Page>, int) =0;
};

#endif // PAGE_ALGORITHM_HPP
