#ifndef JOB_H
#define JOB_H

#include <string>
#include <queue>

struct Access {
  int time, position;
};

class Job
{
private:
  int startTime_;
  int endTime_;
  std::string name_;
  std::queue<Access> accesses_;

public:
  int getStartTime();
  int getEndTime();
  std::string getName();

  Job* setStartTime(int startTime);
  Job* setEndTime(int endTime);
  Job* setName(std::string name);

  Job* addAccess(Access& accesses);
  Access& peakAccess();
  Access& getNextAccess();
  bool hasAccessess();
};

#endif // JOB_H