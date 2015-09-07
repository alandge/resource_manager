/* ComputeCluster.cpp
 *
 * Keeps track of the state of the cluster at any given time. The simulator
 * updates the status of the cluster based on the jobs scheduled by the
 * schedular
 *
 */

#include "ComputeCluster.h"
#include <iostream>

ComputeCluster::ComputeCluster(int num_nodes, int resources_per_node) {

  mNumNodes = num_nodes;
  mNumResourcesPerNode = resources_per_node;

  mNodes.resize(num_nodes);
  for (int i=0; i<num_nodes; i++) {
    ComputeNode* node = new ComputeNode(i, resources_per_node);
    mNodes[i] = node;
  }
}

ComputeCluster::~ComputeCluster() {

  for (int i=0; i<mNodes.size(); i++) {
  
    delete mNodes[i];
  }
}

NodeResourcePairs* ComputeCluster::updateState() {

  NodeResourcePairs* status = new NodeResourcePairs();

  for (int i=0; i<mNodes.size(); i++) {
  
    if (mNodes[i]->updateState()) {
      status->push_back(std::pair<int, int> (mNodes[i]->id(), 
                                       mNodes[i]->availableResources()));
    }
  }

  return status;
}


void ComputeCluster::runJobs(NodeJobPairs* scheduled_jobs) {
  
  NodeJobPairs::iterator it;
  for (it=scheduled_jobs->begin(); it!=scheduled_jobs->end(); it++) {
    mNodes[it->first]->runJob(it->second);
  }
}



void ComputeCluster::printClusterState() {

  for (int i=0; i<mNodes.size(); i++ ) {
  
    std::cout << "(" << mNodes[i]->id() << ", " 
              << mNodes[i]->availableResources() << ")  "; 
  }
  std::cout << "\n";
}

