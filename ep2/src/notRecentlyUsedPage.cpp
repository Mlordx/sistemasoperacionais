#include "notRecentlyUsedPage.hpp"
#include <iostream>

using namespace std;

int NotRecentlyUsedPage::readPage(vector<Page>& pageTable, int page){
  if(pageTable[page].posReal != -1)
    return page;
  if(pageTable[page].posVirtual == -1)
    return -1;

  for(int i = 0; i < (int) pageTable.size(); i++){
    if(pageTable[i].posReal == -1)
      continue;
    if(!pageTable[i].read)
      return i;
  }

  for(int i = 0; i < (int) pageTable.size(); i++){
    if(pageTable[i].posReal == -1)
      continue;
    return i;
  }
  return -1;
}