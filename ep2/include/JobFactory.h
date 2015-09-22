#ifndef JOB_FACTORY_H
#define JOB_FACTORY_H

#include <string>

class Job
{
public:
  vector<Job> createManyJobs(int maxStartTime, int maxEndTime, string nameTemplate, int maxAccess);
  Job createJob(int maxStartTime, int maxEndTime, string nameTemplate, int maxAccess);
};

#endif // JOB_FACTORY_H