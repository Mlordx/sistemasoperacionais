#include <iostream>
#include <memory>

#include "job.hpp"

using namespace std;

shared_ptr<Job> Job::addAccess(Access& access){
  accesses_.push(access);
  return shared_from_this();
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

shared_ptr<Job> Job::setStartTime(int startTime){
  startTime_ = startTime;
  return shared_from_this();
}

int Job::getEndTime(){
  return endTime_;
}

shared_ptr<Job> Job::setEndTime(int endTime){
  endTime_ = endTime;
  return shared_from_this();
}

int Job::getSize(){
  return size_;
}

shared_ptr<Job> Job::setSize(int size){
  size_ = size;
  return shared_from_this();
}

int Job::getId(){
  return id_;
}

shared_ptr<Job> Job::setId(int id){
  id_ = id;
  return shared_from_this();
}

string Job::getName(){
  return name_;
}

shared_ptr<Job> Job::setName(string name){
  name_ = name;
  return shared_from_this();
}

ostream& operator<<(ostream &os, Job const &job){
  os << "name: "  <<  job.name_ << endl <<  "start time: " << job.startTime_ << endl << "end time: " << job.endTime_ << endl;
  return os;
}
