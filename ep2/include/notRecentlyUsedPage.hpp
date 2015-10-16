/************************
EP2 - SO
Vinícius Silva - 7557626
Mateus Barros - 7991037

*************************/

#ifndef NOT_RECENTLY_USED_PAGE_HPP
#define NOT_RECENTLY_USED_PAGE_HPP

#include <vector>

#include "memory.hpp"
#include "pageAlgorithm.hpp"

class NotRecentlyUsedPage : public PageAlgorithm {
public:
  int readPage(std::vector<Page>&, int);
};

#endif // NOT_RECENTLY_USED_PAGE_HPP
