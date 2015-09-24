#include <iostream>
#include <fstream>
#include <algorithm> 

#include "jobFactory.hpp"
#include <string.h>

using namespace std;

vector<int> makeAccessTimes(int, int, int);
bool ascending(int i, int j) { return i > j; }
int randomUpTo(int ceiling) { return rand() % ceiling + 1; }

JobFactory::JobFactory(int sd) : seed(sd){
  srand(seed);
}

Job* JobFactory::createJobRandomly(int maxStartTime, int maxEndTime, string name, int maxAccess){
  
  int startTime = randomUpTo(maxStartTime);
  int endTime = randomUpTo(maxEndTime - startTime) + startTime;
  maxAccess = min(maxAccess, endTime - startTime);
  int nAccess = randomUpTo(maxAccess);
  int memorySize = randomUpTo(MEMORY_SIZE);
  
  Job* job = new Job;
  job->setStartTime(startTime)->setEndTime(endTime)->setName(name);
  vector<int> accessTimes = makeAccessTimes(startTime, endTime, nAccess);

  for(int i = 0; i < nAccess; i++){
    Access* access = new Access(accessTimes.back(),randomUpTo(memorySize-1));
    accessTimes.pop_back();
    job->addAccess(*access);
  }

  return job;
}

vector<Job> JobFactory::createManyJobsRandomly(int maxStartTime, int maxEndTime, std::string nameTemplate, int maxAccess, int nJobs){
  
  vector<Job> jobs;
  for(int i = 0; i < nJobs; i++){
    string name = nameTemplate + to_string(i);
    jobs.push_back(*createJobRandomly(maxStartTime, maxEndTime, name, maxAccess));
  }

  return jobs;
}

Job* JobFactory::createJobFromDescription(string description){
  
  Job* job = new Job;
  job->setStartTime(atoi(strtok((char*) description.c_str(), " ")));
  string name(strtok(NULL, " "));
  job->setName(name);
  job->setEndTime(atoi(strtok(NULL, " ")));
  char * nextToken;
  while((nextToken = strtok(NULL, " ")) != NULL){
    Access* access = new Access(atoi(nextToken), atoi(strtok(NULL, " ")));
    job->addAccess(*access);
  }
  return job;
}

vector<Job> JobFactory::createJobsFromFile(string fileName, int* total, int* virt){

  vector<Job> jobs;
  ifstream file;
  file.open(fileName);
  string description;

  getline(file, description);
  *total = atoi(strtok((char*) description.c_str(), " "));
  *virt = atoi(strtok(NULL, " "));

  while(getline(file, description)){
    jobs.push_back(*createJobFromDescription(description));
  }
  file.close();
  return jobs;
}

vector<int> makeAccessTimes(int startTime, int endTime, int nAccess){
  
  vector<int> possibleAccessTimes;

  for (int i = startTime; i <= endTime; i++){
    possibleAccessTimes.push_back(i);
  }

  random_shuffle(possibleAccessTimes.begin(), possibleAccessTimes.end());

  auto first = possibleAccessTimes.begin();
  auto last = possibleAccessTimes.begin() + nAccess;
  vector<int> accessTimes(first, last);
  sort(accessTimes.begin(), accessTimes.end(), ascending);

  return accessTimes;
}
