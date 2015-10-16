#include <iostream>
#include <fstream>
#include <algorithm> 

#include "jobFactory.hpp"
#include <string.h>

using namespace std;

// int main(){
//   JobFactory factory(40);
//   int nJobs = 100;
//   for(int i = 0; i < 30; i++){
//     auto jobs = factory.createManyJobsRandomly(5, 20, "job_", 64, 20, nJobs);
//     ofstream testFile;
//     testFile.open ("testes/teste" + to_string(nJobs) + "_" + to_string(i)  +".txt");
//     testFile << "4096 512\n";
//     for(int i = 0; i < nJobs; i++){
//       testFile << 
//       jobs[i].getStartTime() << " " <<
//       jobs[i].getName() << " " <<
//       jobs[i].getEndTime() << " " <<
//       jobs[i].getSize() << " ";
//       while(jobs[i].hasAccesses()){
//         auto access = jobs[i].getNextAccess();
//         testFile << 
//         access.position << " " <<
//         access.time << " ";
//       }
//       testFile << endl;
//     }
//     testFile.close();
//   }
// }

vector<int> makeAccessTimes(int, int, int);
bool ascending(int i, int j) { return i > j; }
inline int randomUpTo(int ceiling) { return rand() % ceiling + 1; }

JobFactory::JobFactory(int sd) : seed(sd){
  srand(seed);
}

shared_ptr<Job> JobFactory::createJobRandomly(int id, int maxStartTime, int maxEndTime, string name, int maxSize, int maxAccess){
  
  int startTime = randomUpTo(maxStartTime);
  int endTime = randomUpTo(maxEndTime - startTime) + startTime;
  maxAccess = min(maxAccess, endTime - startTime);
  int nAccess = randomUpTo(maxAccess);
  int memorySize = randomUpTo(maxSize - maxSize/10 - 1 ) + 1 + maxSize/10;
  
  shared_ptr<Job> job(new Job);
  job->setId(id);
  job->setStartTime(startTime);
  job->setEndTime(endTime);
  job->setName(name);
  job->setSize(memorySize);
  vector<int> accessTimes = makeAccessTimes(startTime, endTime, nAccess);

  for(int i = 0; i < nAccess; i++){
    shared_ptr<Access> access(new Access(randomUpTo(memorySize-1), accessTimes.back()));
    accessTimes.pop_back();
    job->addAccess(*access);
  }

  return job;
}
  
vector<Job> JobFactory::createManyJobsRandomly(int maxStartTime, int maxEndTime, std::string nameTemplate, int maxSize, int maxAccess, int nJobs){
  
  vector<Job> jobs;
  for(int i = 0; i < nJobs; i++){
    string name = nameTemplate + to_string(i);
    jobs.push_back(*createJobRandomly(i, maxStartTime, maxEndTime, name, maxSize, maxAccess));
  }

  return jobs;
}

shared_ptr<Job> JobFactory::createJobFromDescription(int id, string description){
  
  shared_ptr<Job> job(new Job);
  job->setId(id);
  job->setStartTime(atoi(strtok((char*) description.c_str(), " ")));
  string name(strtok(nullptr, " "));
  job->setName(name);
  job->setEndTime(atoi(strtok(nullptr, " ")));
  job->setSize(atoi(strtok(nullptr, " ")));
  char * nextToken;
  while((nextToken = strtok(nullptr, " ")) != nullptr){
    shared_ptr<Access> access(new Access(atoi(nextToken), atoi(strtok(nullptr, " "))));
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
  *virt = atoi(strtok(nullptr, " "));
  int nextId = 0;
  while(getline(file, description)){
    jobs.push_back(*createJobFromDescription(nextId, description));
    nextId++;
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
