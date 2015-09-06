/* Schedular.h
 *
 * Base class that implements a schedular
 *
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>

struct NodeStatus{
  int availableResources;
  int nodeId;
};

class Scheduler {

public:

  Scheduler() {}
  ~Scheduler() {}

  std::vector< std::pair<int, Job*> >* getScheduledJobs() {}


private:

  virtual void scheduleJobs() {}

  std::queue<Job*> mJobQ;

  //! Scheduled jobs with tuples(nodeId, Job)
  std::vector< std::pair<int, Job*> > *mScheduledJobs;

  //! Scheduler maintains state of every node in terms of available resources
  std::vector<NodeStatus> mNodesStatus;
};



#endif /*SCHEDULER_H*/



