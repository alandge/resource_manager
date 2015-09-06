/* ComputeNode.h
 *
 * Class that represents a single compute node in the cluster.
 *
 */

#ifndef COMPUTENODE_H
#define COMPUTENODE_H
#include <list>
#include "Job.h"

class ComputeNode {

public:
  ComputeNode(int id, int num_resources) : mId(id), mNumResources(num_resources) 
  {
    mAvailableResources = mNumResources;
  }

  ~ComputeNode() {}

  int id() { return mId; }

  //! place a job to this node
  void addJob(Job& job);

  //! return free resources on the node
  int availableResources() { return mAvailableResources; }

  //! Access to running jobs on this node
  const std::list<Job*> runningJobs() { return mJobs; }

  //! Update the state of the running jobs after a timestep.
  //! Terminate jobs that are complete. If there is change in the number of
  //  available resources return true else false. 
  bool updateState();

private:
  
  int mId;
  int mNumResources;
  int mAvailableResources;
  std::list<Job*> mJobs;

};

#endif /*COMPUTENODE_H*/
