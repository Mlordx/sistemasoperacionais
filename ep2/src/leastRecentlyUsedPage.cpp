#include <iostream>
#include "leastRecentlyUsedPage.hpp"
#include <algorithm> 

using namespace std;

inline bool accessAscending(Page a, Page b) { return a.accessNumber < b.accessNumber; }
inline bool positionAscending(Page a, Page b) { return a.posVirtual < b.posVirtual; }

int LeastRecentlyUsedPage::readPage(vector<Page>& pageTable, int page){
  if(pageTable[page].posReal != -1)
    return page;
  if(pageTable[page].posVirtual == -1)
    return -1;

  sort(pageTable.begin(), pageTable.end(), accessAscending);

  for(int i = 0; i < (int) pageTable.size(); i++){
    if(pageTable[i].posReal == -1)
      continue;
    int out = pageTable[i].posVirtual/PAGE_SIZE;
    sort(pageTable.begin(), pageTable.end(), positionAscending);  
    return out;
  }

  sort(pageTable.begin(), pageTable.end(), positionAscending);  
  return -1;
}