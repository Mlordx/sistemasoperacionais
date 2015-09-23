#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include <queue>

struct Access {
  int time, position;
};


class Job{
  
private:
  int startTime_;
  int endTime_;
  std::string name_;
  std::queue<Access> accesses_;

public:
  Job* addAccess(Access&);
  Access& peakAccess();
  Access& getNextAccess();
  bool hasAccesses();

  int getStartTime();
  int getEndTime();
  std::string getName();

  Job* setStartTime(int);
  Job* setEndTime(int);
  Job* setName(std::string);

  std::string toString();
};

#endif // JOB_HPP
