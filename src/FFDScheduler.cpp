/* FFDScheduler.cpp
 *
 * Uses the first fit decreasing approach to assign a node to a job. Maintains
 * separate queue for jobs that have reached max wait time and give them
 * priority over other jobs to avoid starvation.
 *
 */

#include "FFDScheduler.h"
#include <iostream>
#include <cassert>



void FFDScheduler::initialize(int cluster_size, 
                                  NodeResourcePairs* cluster_state) {
  
  mNodesStatus.resize(cluster_size);

  NodeResourcePairs::iterator it;
  // First update status of the nodes
  for (it=cluster_state->begin(); it!=cluster_state->end(); it++ ) {
    assert(it->first < mNodesStatus.size());
    mNodesStatus[it->first] = it->second;
  }

}


NodeJobPairs* FFDScheduler::getScheduledJobs(  
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

  Job* job;

  // First check if any jobs have reached max wait time. Schedule those jobs on
  // priority by waiting for resources to become available.
  while (!mWaitTimeQ.empty()) {
    job = mWaitTimeQ.front();

    job->updateTime();
    
    bool scheduled = false;

    for (int i=0 ; i<mNodesStatus.size(); i++) {
      if ((mNodesStatus[i] >= job->numResources()) ){ 
        mScheduledJobs->push_back(std::pair<int, Job*>(i,job));
        mNodesStatus[i]-= job->numResources();
        mWaitTimeQ.pop();
        scheduled = true;
        break;
      }
    }

    if (!scheduled) {
      break;
    }
  }
 

  // Go through the JobQ and update wait time. If no jobs are in the waitTimeQ
  // try and schedule jobs from JobQ.

  std::queue<Job*> tempQ;
  
  while(!mJobQ.empty()) {
  
    Job* job = mJobQ.top();
    
    // increment wait time
    job->updateTime();

    std::vector<NodeId_t>::iterator n_it;

    bool scheduled = false;

    if (mWaitTimeQ.empty()) {
      for (int i=0 ; i<mNodesStatus.size(); i++) {
        if ((mNodesStatus[i] >= job->numResources()) ){ 
          mScheduledJobs->push_back(std::pair<int, Job*>(i,job));
          mNodesStatus[i]-= job->numResources();
          mJobQ.pop();
          scheduled = true;
          break;
        }
      }
    }

    // if no resources are available we wait till they are available
    if (!scheduled) { 
      if (job->waitTime() < mMaxJobWaitTime) {
        tempQ.push(job);
      }
      else {
        mWaitTimeQ.push(job);
      }
      
      mJobQ.pop();
    }

  }

  while (!tempQ.empty()) {
    mJobQ.push(tempQ.front());
    tempQ.pop();
  }

  return mScheduledJobs; 

}

void FFDScheduler::printJobQ() {

  std::priority_queue<Job*, std::vector<Job*>, JobComp> temp(mJobQ);

  std::cerr << "JobQ: (id, resources, duration)::";
    
  while(!temp.empty()) {
    
    Job* job = temp.top();
    std::cout << "(" << job->id() << ", " << job->numResources()
              << ", " << job->duration() << ")  ";
    temp.pop();
  }

  std::cout << "\n";

  std::cout << "WaitQ: (id, resources, duration):: ";
  std::queue<Job*> temp1(mWaitTimeQ);
    
  while(!temp1.empty()) {
    
    Job* job = temp1.front();
    std::cout << "(" << job->id() << ", " << job->numResources()
              << ", " << job->duration() << ")  ";
    temp1.pop();
  }

  std::cout << "\n";


}

