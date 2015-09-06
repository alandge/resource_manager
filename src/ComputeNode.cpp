/* ComputeNode.cpp
 *
 */


#include "ComputeNode.h"
#include "Job.h"
#include <cassert>


bool ComputeNode::updateState() {

  bool status_changed = false;
  
  if (mJobs.size()==0) {
    return true;
  }

  std::list<Job*>::iterator it;

  for(it = mJobs.begin(); it != mJobs.end(); it++) {
    (*it)->updateTime();
    if((*it)->status() == EXECUTED) {
      mJobs.erase(it);
      mAvailableResources+= (*it)->numResources();
      status_changed = true;
    }
  }

  return status_changed;
  
}

void ComputeNode::addJob(Job& job) {
  
  assert(job.duration() <= mAvailableResources);

  job.status(RUNNING);
  mJobs.push_back(&job);

}
