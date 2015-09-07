/* BestFitScheduler.cpp
 *
 * Uses the best fit approach to assign a node to a job
 *
 */

#include "BestFitScheduler.h"
#include <iostream>
#include <cassert>



void BestFitScheduler::initialize(int cluster_size, 
                                  NodeResourcePairs* cluster_state) {
  
  mNodesStatus.resize(cluster_size);

  NodeResourcePairs::iterator it;
  // First update status of the nodes
  for (it=cluster_state->begin(); it!=cluster_state->end(); it++ ) {
    assert(it->first < mNodesStatus.size());
    mNodesStatus[it->first] = it->second;
  }

}


NodeJobPairs* BestFitScheduler::getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_state) {

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
  
    Job* job = mJobQ.top();

    std::vector<NodeId_t>::iterator n_it;

    bool scheduled = false;

    //for (n_it=mNodesStatus.begin(); n_it!=mNodesStatus.end(); n_it++) {
    for (int i=0 ; i<mNodesStatus.size(); i++) {
      if ((mNodesStatus[i] >= job->numResources()) ){// && 
          //(mNodesStatus[i] <= job->numResources() + mThreshold)  ) {
        mScheduledJobs->push_back(std::pair<int, Job*>(i,job));
        mNodesStatus[i]-= job->numResources();
        mJobQ.pop();
        scheduled = true;
        break;
      }
    }

    // if no resources are available we push this on a separate waiting queue
    if (!scheduled) {
      mWaitQ.push(job);
      mJobQ.pop();
      //break;
    }

  }

  while (!mWaitQ.empty()) {
    mJobQ.push(mWaitQ.front());
    mWaitQ.pop();
  }

  return mScheduledJobs; 

}

void BestFitScheduler::printJobQ() {

  //std::cout << "JobQ: (id, resources, duration): ";
  std::priority_queue<Job*, std::vector<Job*>, JobComp> temp(mJobQ);

  std::cerr << "JobQ: (id, resources, duration):";
    
  while(!temp.empty()) {
    
    Job* job = temp.top();
    std::cout << "(" << job->id() << ", " << job->numResources()
              << ", " << job->duration() << ")  ";
    temp.pop();
  }

  std::cout << "\n";

  std::cout << "WaitQ: (id, resources, duration): ";
  std::queue<Job*> temp1(mWaitQ);
    
  while(!temp1.empty()) {
    
    Job* job = temp1.front();
    std::cout << "(" << job->id() << ", " << job->numResources()
              << ", " << job->duration() << ")  ";
    temp1.pop();
  }

  std::cout << "\n";


}

