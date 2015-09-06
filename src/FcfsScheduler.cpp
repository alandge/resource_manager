/* FcfsScheduler.cpp
 *
 * Simple FCFS scheduler
 *
 */

#include "FcfsScheduler.h"
#include <iostream>

NodeJobPairs* FcfsScheduler :: getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_state)
{

  mScheduledJobs = new NodeJobPairs();
  NodeResourcePairs::iterator it;

  // First update status of the nodes
  for (it=cluster_state->begin(); it!=cluster_state->end(); it++ ) {
    mNodesStatus[it->first] = it->second;
  }

  // add input jobs to the queue
  for (int i=0; i<input_jobs.size(); i++) {
    mJobQ.push(input_jobs[i]);
  }

  
  while(!mJobQ.empty()) {
  
    Job* job = mJobQ.front();

    std::map<NodeId_t, int>::iterator p_it;

    for (p_it=mNodesStatus.begin(); p_it!=mNodesStatus.end(); p_it++) {
      if (p_it->second >= job->numResources()) {
        mScheduledJobs->push_back(std::pair<int, Job*>(p_it->first,job));
        p_it->second-= job->numResources();
        mJobQ.pop();
        break;
      }
    }

    // if no resources are available we wait as this is fcfs
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

