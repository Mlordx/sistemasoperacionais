#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include <queue>
#include <memory>

struct Access {
  int time, position;

  Access(int a, int b) : time(a), position(b){}
  
};


class Job: public std::enable_shared_from_this<Job> {
  
private:
  int startTime_;
  int endTime_;
  std::string name_;
  std::queue<Access> accesses_;

public:
  std::shared_ptr<Job> addAccess(Access&);
  Access& peakAccess();
  Access& getNextAccess();
  bool hasAccesses();

  int getStartTime();
  int getEndTime();
  std::string getName();

  std::shared_ptr<Job> setStartTime(int);
  std::shared_ptr<Job> setEndTime(int);
  std::shared_ptr<Job> setName(std::string);
  friend std::ostream& operator<<(std::ostream&, const Job&);
};

#endif // JOB_HPP
