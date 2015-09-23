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

  Job* createJob(int, int, std::string, int);
  
  std::vector<Job> createManyJobs(int, int, std::string, int, int);
};

#endif // JOB_FACTORY_H
