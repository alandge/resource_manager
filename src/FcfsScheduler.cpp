/* FcfsScheduler.cpp
 *
 * Simple FCFS scheduler
 *
 */

#include "FcfsScheduler.h"
#include <iostream>
#include <cassert>

void FcfsScheduler::initialize(int cluster_size, 
                                  NodeResourcePairs* cluster_state) {
  
  mNodesStatus.resize(cluster_size);

  NodeResourcePairs::iterator it;
  for (it=cluster_state->begin(); it!=cluster_state->end(); it++ ) {
    assert(it->first < mNodesStatus.size());
    mNodesStatus[it->first] = it->second;
  }

}



NodeJobPairs* FcfsScheduler :: getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_state)
{

  mScheduledJobs = new NodeJobPairs();
  NodeResourcePairs::iterator it;

  // First update status of the nodes
  for (it=cluster_state->begin(); it!=cluster_state->end(); it++ ) {
    assert(it->first < mNodesStatus.size());
    mNodesStatus[it->first] = it->second;
  }

  // add input jobs to the queue
  for (int i=0; i<input_jobs.size(); i++) {
    mJobQ.push(input_jobs[i]);
  }

  
  while(!mJobQ.empty()) {
  
    Job* job = mJobQ.front();

    std::map<NodeId_t, int>::iterator p_it;

    for (int i=0 ; i<mNodesStatus.size(); i++) {
      if ((mNodesStatus[i] >= job->numResources()) ){ 
        mScheduledJobs->push_back(std::pair<int, Job*>(i,job));
        mNodesStatus[i]-= job->numResources();
        mJobQ.pop();
        break;
      }
    }

    // if no resources are available we wait as this is fcfs and update time for
    // rest of the jobs
    if (job == mJobQ.front())
      break;
  
  }

  return mScheduledJobs;


}

void FcfsScheduler::printJobQ() {

  std::cout << "JobQ: (id, resources, duration): ";
  std::queue<Job*> temp(mJobQ);
    
  while(!temp.empty()) {
    
    Job* job = temp.front();
    std::cout << "(" << job->id() << ", " << job->numResources()
              << ", " << job->duration() << ")  ";
    temp.pop();
  }

  std::cout << "\n";
}

