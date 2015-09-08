/* BestFitScheduler.cpp
 *
 * Uses the best fit approach to assign a node to a job
 *
 */

#ifndef BESTFITSCHEDULER_H
#define BESTFITSCHEDULER_H

#include "Scheduler.h"
#include <queue>

class JobComp
{
public:

  bool operator()(Job* A, Job* B) const  {
    if (A->numResources() != B->numResources())
      return (A->numResources() < B->numResources());
    else
      return (A->id() > B->id());
  }
};


class BestFitScheduler : public Scheduler {

public :

  BestFitScheduler(int max_job_wait_time) : mMaxJobWaitTime(max_job_wait_time){}

  ~BestFitScheduler() {}

  virtual void initialize(int cluster_size, NodeResourcePairs* cluster_state);

  virtual NodeJobPairs* getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_state);

  virtual void printJobQ();

private:
  //! Scheduler maintains state of every node in terms of available resources
  std::vector<NodeId_t> mNodesStatus;

  //! Priority queue for the pending jobs mainting jobs in descending order of
  //the number of resources required
  std::priority_queue<Job*, std::vector<Job*>, JobComp> mJobQ; 


  std::queue<Job*> mWaitTimeQ;

  //! Threshold for determining best fit
  int mMaxJobWaitTime;
 

};

#endif /*BESTFITSCHEDULER_H*/

