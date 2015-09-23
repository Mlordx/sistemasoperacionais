#include <iostream>

#include "Job.hpp"

using namespace std;

Job* Job::addAccess(Access& access){
  accesses_.push(access);
  return this;
}

Access& Job::peakAccess(){
  return accesses_.front();
}

Access& Job::getNextAccess(){
  Access& access = accesses_.front();
  accesses_.pop();
  return access;
}

bool Job::hasAccesses(){
  return !accesses_.empty();
}

int Job::getStartTime(){
  return startTime_;
}

Job* Job::setStartTime(int startTime){
  startTime_ = startTime;
  return this;
}

int Job::getEndTime(){
  return endTime_;
}

Job* Job::setEndTime(int endTime){
  endTime_ = endTime;
  return this;
}

string Job::getName(){
  return name_;
}

Job* Job::setName(string name){
  name_ = name;
  return this;
}


string Job::toString(){
  return "name: " + name_ + "\n" + "start time: " + to_string(startTime_) + "\n" + "end time: " + to_string(endTime_) + "\n";
}
