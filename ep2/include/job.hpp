/************************
EP2 - SO
Vinícius Silva - 7557626
Mateus Barros - 7991037

*************************/

#ifndef JOB_HPP
#define JOB_HPP

#include <string>
#include <queue>
#include <memory>

struct Access {
  int position, time;

  Access(int a, int b) : position(a), time(b){}
  
};


class Job: public std::enable_shared_from_this<Job> {
  
private:
  int startTime_;
  int endTime_;
  int size_;
  int id_;
  std::string name_;
  std::queue<Access> accesses_;

public:
  void addAccess(Access&);
  Access& peakAccess();
  Access& getNextAccess();
  bool hasAccesses();

  int getStartTime();
  int getEndTime();
  int getSize();
  int getId();
  std::string getName();

  void setStartTime(int);
  void setEndTime(int);
  void setSize(int);
  void setId(int);
  void setName(std::string);
  friend std::ostream& operator<<(std::ostream&, const Job&);
};

#endif // JOB_HPP
