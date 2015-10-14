#include <iostream>
#include <memory>

#include "job.hpp"

using namespace std;

void Job::addAccess(Access& access){
  accesses_.push(access);
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

void Job::setStartTime(int startTime){
  startTime_ = startTime;
}

int Job::getEndTime(){
  return endTime_;
}

void Job::setEndTime(int endTime){
  endTime_ = endTime;
}

int Job::getSize(){
  return size_;
}

void Job::setSize(int size){
  size_ = size;
}

int Job::getId(){
  return id_;
}

void Job::setId(int id){
  id_ = id;
}

string Job::getName(){
  return name_;
}

void Job::setName(string name){
  name_ = name;
}

ostream& operator<<(ostream &os, Job const &job){
  os << "id: "  <<  job.id_ << endl
  << "name: "  <<  job.name_ << endl
  << "start time: " << job.startTime_ << endl
  << "end time: " << job.endTime_ << endl
  << "size: " << job.size_ << endl;
  return os;
}
