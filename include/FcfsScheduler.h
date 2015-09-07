/* FcfsScheduler.h
 *
 * Simple First Come First Serve schedular
 *
 */

#ifndef FCFSSCHEDULER_H
#define FCFSSCHEDULER_H

#include "Scheduler.h"
#include <map>

class FcfsScheduler : public Scheduler {

public:
  FcfsScheduler() {}

  ~FcfsScheduler() {}

  virtual NodeJobPairs* getScheduledJobs(  
                              std::vector<Job*>& input_jobs,
                              NodeResourcePairs* cluster_status);

  virtual void printJobQ();

private:

  //! queue for pending jobs
  std::queue<Job*> mJobQ;

  //! Scheduler maintains state of every node in terms of available resources
  std::map<NodeId_t, int> mNodesStatus;
 

};

#endif /*FCFSSCHEDULER_H*/

