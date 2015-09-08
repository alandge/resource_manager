/* InputGenerator.h
 *
 * Generates the input stream in terms of tuples of available resources and the
 * job requests
 *
 */

#ifndef INPUTGENERATOR_H
#define INPUTGENERATOR_H

#include <vector>
#include <random>

typedef std::vector< std::pair<int, int> > JobResourceTimePairs; 
typedef std::pair<int, int> JobResourceTimePair;
class InputGenerator {

public:
  InputGenerator(int num_compute_nodes, int max_res_per_node, 
                 int max_time_per_job) : 
                 mNumComputeNodes(num_compute_nodes), 
                 mMaxResourcesPerNode(max_res_per_node),
                 mMaxTimePerJob(max_time_per_job) {}

  ~InputGenerator() {}


  JobResourceTimePair generateJob(std::default_random_engine generator);


private:

  int mNumComputeNodes;
  int mMaxResourcesPerNode;
  int mMaxJobsPerTimestep;
  int mMaxTimePerJob;
};

#endif /*INPUTGENERATOR_H*/
