#ifndef JOB_FACTORY_H
#define JOB_FACTORY_H

#include <string>
#include <vector>

#include <Job.h>
#define MEMORY_SIZE 100

class JobFactory
{
public:
  JobFactory(int seed);

  Job* createJob(int maxStartTime, int maxEndTime, std::string nameTemplate, int maxAccess);
  
  std::vector<Job> createManyJobs(int maxStartTime, 
                                  int maxEndTime, 
                                  std::string nameTemplate, 
                                  int maxAccess);
};

#endif // JOB_FACTORY_H