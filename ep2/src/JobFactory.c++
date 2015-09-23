#include <iostream>
#include <algorithm> 

#include "JobFactory.h"

using namespace std;

bool ascending(int i, int j) { return i > j; }
vector<int> makeAccessTimes(int startTime, int endTime, int nAccess);

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
  int memorySize = rand() % MEMORY_SIZE + 1;
  int accesses[nAccess];
  Job* job = new Job;
  job->setStartTime(startTime)->setEndTime(endTime)->setName(name);
  vector<int> accessTimes = makeAccessTimes(startTime, endTime, nAccess);

  for(int i = 0; i < nAccess; i++){
    Access* access = new Access;
    access->time = accessTimes.back();
    accessTimes.pop_back();
    access->position = rand() % memorySize;
    job->addAccess(*access);
  }

  return job;
}

vector<Job> JobFactory::createManyJobs( int maxStartTime, 
                                        int maxEndTime, 
                                        std::string nameTemplate, 
                                        int maxAccess,
                                        int nJobs)
{
  vector<Job> jobs;
  for(int i = 0; i < nJobs; i++){
    string name = nameTemplate + to_string(i);
    jobs.push_back(*createJob(maxStartTime, maxEndTime, name, maxAccess));
  }
  return jobs;
}

vector<int> makeAccessTimes(int startTime, int endTime, int nAccess)
{
  vector<int> possibleAccessTimes;

  for (int i = startTime; i <= endTime; i++){
    possibleAccessTimes.push_back(i);
  }

  random_shuffle(possibleAccessTimes.begin(), possibleAccessTimes.end());

  vector<int>::const_iterator first = possibleAccessTimes.begin();
  vector<int>::const_iterator last = possibleAccessTimes.begin() + nAccess;
  vector<int> accessTimes(first, last);
  sort(accessTimes.begin(), accessTimes.end(), ascending);

  return accessTimes;
}