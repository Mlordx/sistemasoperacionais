#include <iostream>

#include "Job.h"

using namespace std;    

int main()
{
  Job* job = new Job;
  Access acc1, acc2, acc3;
  job->setStartTime(37)->setEndTime(58)->setName("processo");

  cout << job->getStartTime() << endl;
  cout << job->getEndTime() << endl;
  cout << job->getName() << endl;

  acc1.position = 3;
  acc2.position = 7;
  acc3.position = 12;

  acc1.time = 1;
  acc2.time = 2;
  acc3.time = 3;

  cout << job->hasAccessess() << endl;
  job->addAccess(acc1);
  cout << job->hasAccessess() << endl;
  job->addAccess(acc2)->addAccess(acc3);
  cout << "time : " << job->peakAccess().time 
  		 << ", position: " << job->peakAccess().position << endl;
  job->peakAccess().time = 738;
  cout << "time : " << job->getNextAccess().time 
  		 << ", position: " << job->peakAccess().position << endl;
  cout << "time : " << job->getNextAccess().time 
  		 << ", position: " << job->peakAccess().position << endl;
  cout << "time : " << job->getNextAccess().time 
  		 << ", position: " << job->peakAccess().position << endl;
  cout << job->hasAccessess() << endl;

  delete job;

  return 0;
}

int Job::getStartTime()
{
  return startTime_;
}

Job* Job::setStartTime(int startTime)
{
  startTime_ = startTime;
  return this;
}

int Job::getEndTime()
{
  return endTime_;
}

Job* Job::setEndTime(int endTime)
{
  endTime_ = endTime;
  return this;
}

string Job::getName()
{
  return name_;
}

Job* Job::setName(string name)
{
  name_ = name;
  return this;
}

Job* Job::addAccess(Access& access)
{
	accesses_.push(access);
	return this;
}

Access& Job::peakAccess()
{
	return accesses_.front();
}

Access& Job::getNextAccess()
{
	Access& access = accesses_.front();
	accesses_.pop();
	return access;
}

bool Job::hasAccessess()
{
	return !accesses_.empty();
}

ostream Job::toString()
{
	ostream strm;
  return strm << 
  "nome: " << job.nome_ << endl <<
  "start time: " << job.startTime_ << endl <<
  "end time: " << job.endTime_ << endl;
}