#ifndef JOB_FACTORY_H
#define JOB_FACTORY_H

#include <string>
#include <vector>

#include <job.hpp>
#define MEMORY_SIZE 100

class JobFactory{
  int seed;
public:
  JobFactory(int s);

  Job* createJobRandomly(int, int, std::string, int);
  
  std::vector<Job> createManyJobsRandomly(int, int, std::string, int, int);
  
  Job* createJobFromDescription(std::string);

  std::vector<Job> createJobsFromFile(std::string, int*, int*);
};

#endif // JOB_FACTORY_H
