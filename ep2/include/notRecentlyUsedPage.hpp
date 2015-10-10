#ifndef NOT_RECENTLY_USED_PAGE_HPP
#define NOT_RECENTLY_USED_PAGE_HPP

class notRecentlyUsedPage : public PageAlgorithm{
private:
  std::shared_ptr<MemorySlot> next_;
public:
  NextFit(std::shared_ptr<MemorySlot>);
  int execute(Job);
};

#endif // NOT_RECENTLY_USED_PAGE_HPP