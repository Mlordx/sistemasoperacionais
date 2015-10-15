#include <iostream>
#include "firstInFirstOut.hpp"
#include <algorithm> 

using namespace std;

inline bool pageAscending(Page a, Page b) { return a.pageNumber < b.pageNumber; }
inline bool positionAscending(Page a, Page b) { return a.posVirtual < b.posVirtual; }

int FirstInFirstOut::readPage(vector<Page>& pageTable, int page){
  if(pageTable[page].posReal != -1)
    return page;
  if(pageTable[page].posVirtual == -1)
    return -1;

  sort(pageTable.begin(), pageTable.end(), pageAscending);

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