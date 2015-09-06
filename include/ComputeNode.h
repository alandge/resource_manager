/* ComputeNode.h
 *
 * Class that represents a single compute node in the cluster.
 *
 */

#ifndef COMPUTENODE_H
#define COMPUTENODE_H
#include <list>
#include <vector>
#include "Job.h"

typedef int NodeId_t;
typedef std::list<Job*> JobList;
typedef std::vector< std::pair<NodeId_t, int> > NodeResourcePairs; 
typedef std::pair<NodeId_t, Job*> NodeJobPair;
typedef std::vector< NodeJobPair > NodeJobPairs; 

class ComputeNode {

public:
  ComputeNode(int id, int num_resources) : mId(id), mNumResources(num_resources) 
  {
    mAvailableResources = mNumResources;
  }

  ~ComputeNode() {}

  int id() { return mId; }

  //! run a job to this node
  void runJob(Job* job);

  //! return free resources on the node
  int availableResources() { return mAvailableResources; }

  //! Access to running jobs on this node
  const JobList runningJobs() { return mJobs; }

  //! Update the state of the running jobs after a timestep.
  //! Terminate jobs that are complete. If there is change in the number of
  //  available resources return true else false. 
  bool updateState();

private:
  
  NodeId_t mId;
  int mNumResources;
  int mAvailableResources;
  JobList mJobs;

};

#endif /*COMPUTENODE_H*/
