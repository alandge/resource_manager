/* ComputeNode.cpp
 *
 */


#include "ComputeNode.h"
#include "Job.h"
#include <cassert>
#include <iostream>
#include <cstdlib>

ComputeNode::ComputeNode(int id, int num_resources) : 
                        mId(id), mNumResources(num_resources) {
  mAvailableResources = mNumResources;
}


bool ComputeNode::updateState() {

  bool status_changed = false;
  
  if (mJobs.size()==0) {
    return true;
  }

  JobList::iterator it = mJobs.begin();

  while( it != mJobs.end()) {
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
