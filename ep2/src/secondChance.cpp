#include <iostream>
#include "secondChance.hpp"
#include <algorithm> 

using namespace std;

bool pageAscending(Page a, Page b) { return a.pageNumber < b.pageNumber; }
bool positionAscending(Page a, Page b) { return a.posVirtual < b.posVirtual; }

int SecondChance::readPage(vector<Page>& pageTable, int page){
  if(pageTable[page].posReal != -1)
    return page;
  if(pageTable[page].posVirtual == -1)
    return -1;


  sort(pageTable.begin(), pageTable.end(), pageAscending);

  while(true){
    for(int i = 0; i < (int) pageTable.size(); i++){
      if(pageTable[i].posReal == -1)
        continue;
      if(pageTable[i].read)
        pageTable[i].read = false;
      else{
        int out = pageTable[i].posVirtual/PAGE_SIZE;
        sort(pageTable.begin(), pageTable.end(), positionAscending);  
        return out;
      }
    }
  }

  sort(pageTable.begin(), pageTable.end(), positionAscending);  
  return -1;
}