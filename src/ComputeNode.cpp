/* ComputeNode.cpp
 *
 */


#include "ComputeNode.h"
#include "Job.h"
#include <cassert>
#include <iostream>


bool ComputeNode::updateState() {

  bool status_changed = false;
  
  if (mJobs.size()==0) {
    return true;
  }

  JobList::iterator it = mJobs.begin();

  while( it != mJobs.end()) {
    (*it)->updateTime();
    //if((*it)->status() == COMPLETED) {
    if((*it)->timeRemaining()==0) {
      mAvailableResources+= (*it)->numResources();
      status_changed = true;
      mJobs.erase(it++);
    }
    else
      it++;
  }

  return status_changed;
  
}

void ComputeNode::runJob(Job* job) {
  
  assert(job->numResources() <= mAvailableResources);

  job->status(RUNNING);
  mJobs.push_back(job);
  mAvailableResources-=job->numResources();

}
