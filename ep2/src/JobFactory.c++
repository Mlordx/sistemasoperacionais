#include <iostream>
#include <algorithm> 

#include "JobFactory.h"

using namespace std;

bool ascending(int i, int j) { return i > j; }

int main(int argc, char* argv[]){
  JobFactory* factory = new JobFactory(atoi(argv[1]));
  Job* job = factory->createJob(90, 100, "processp", 100);
  cout << job->toString();
  while(job->hasAccesses())
    cout << "time: " << job->getNextAccess().time 
         << ", position: " << job->peakAccess().position << endl;
}

JobFactory::JobFactory(int seed)
{
  srand(seed);
}

Job* JobFactory::createJob(int maxStartTime, int maxEndTime, 
                           string name, int maxAccess)
{
  int startTime = rand() % maxStartTime + 1;
  int endTime = rand() % (maxEndTime - startTime) + startTime + 1;
  maxAccess = min(maxAccess, endTime - startTime);
  int nAccess = rand() % maxAccess + 1;
  int accesses[nAccess];
  Job* job = new Job;
  vector<int> possibleAccessTimes;

  job->setStartTime(startTime)->setEndTime(endTime)->setName(name);

  for (int i = 0; i < maxAccess; i++){
    possibleAccessTimes.push_back(i);
  }
  
  random_shuffle(possibleAccessTimes.begin(), possibleAccessTimes.end());

  vector<int>::const_iterator first = possibleAccessTimes.begin();
  vector<int>::const_iterator last = possibleAccessTimes.begin() + nAccess;
  vector<int> accessTimes(first, last);
  sort(accessTimes.begin(), accessTimes.end(), ascending);

  for(int i = 0; i < nAccess; i++){
    Access* access = new Access;
    access->time = accessTimes.back() + startTime;
    accessTimes.pop_back();
    access->position = rand() % MEMORY_SIZE;
    job->addAccess(*access);
  }

  return job;
}