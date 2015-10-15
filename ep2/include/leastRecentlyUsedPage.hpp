#ifndef LEAST_RECENTLY_USED_PAGE_HPP
#define LEAST_RECENTLY_USED_PAGE_HPP

#include <vector>

#include "memory.hpp"
#include "pageAlgorithm.hpp"

class LeastRecentlyUsedPage : public PageAlgorithm {
public:
  int readPage(std::vector<Page>&, int);
};

#endif // LEAST_RECENTLY_USED_PAGE_HPP