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
  virtual ~Scheduler() {}

  virtual void initialize(int cluster_size, NodeResourcePairs* cluster_state) = 0;

  virtual NodeJobPairs* getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_status) = 0;

  virtual void printJobQ() = 0;

protected:
  //! Scheduled jobs with tuples(nodeId, Job).
  // Allocated on head and should be deleted by the simulator
  NodeJobPairs* mScheduledJobs;

  //std::queue<Job*> mJobQ;

   //! Scheduler maintains state of every node in terms of available resources
  //std::vector<NodeStatus> mNodesStatus;

};



#endif /*SCHEDULER_H*/



