/* Schedular.h
 *
 * Base class that implements a schedular
 *
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include "Job.h"
#include "ComputeNode.h"


class Scheduler {

public:

  Scheduler() {}
  ~Scheduler() {}

  virtual NodeJobPairs* getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_status) = 0;

  virtual void printJobQ() = 0;

protected:
  //! Scheduled jobs with tuples(nodeId, Job)
  NodeJobPairs* mScheduledJobs;

  std::queue<Job*> mJobQ;

   //! Scheduler maintains state of every node in terms of available resources
  //std::vector<NodeStatus> mNodesStatus;

};



#endif /*SCHEDULER_H*/



