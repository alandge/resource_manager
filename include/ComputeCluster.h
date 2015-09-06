/* ComputeCluster.h
 *
 * Keeps track of the state of the cluster at any given time. The simulator
 * updates the status of the cluster based on the jobs scheduled by the
 * schedular
 *
 */

#ifndef COMPUTECLUSTER_H
#define COMPUTECLUSTER_H
#include <vector>
#include "ComputeNode.h"

class ComputeCluster{

public:
  ComputeCluster(int num_nodes, int resources_per_node);
  ~ComputeCluster();

  //! returns the changed state of any of the compute nodes in terms of a
  //! tuple(nodeId, avail_resources). We can have multiple of such updates in a
  //! timestep, hence returing a vector of tuples
  std::vector< std::pair<int, int> > updateState();

private:
  int mNumNodes;
  int mNumResourcesPerNode;

  std::vector<ComputeNode*> mNodes;

};



#endif /*COMPUTECLUSTER_H*/

