/* InputGenerator.h
 *
 * Generates the input stream in terms of tuples of available resources and the
 * job requests
 *
 */

#ifndef INPUTGENERATOR_H
#define INPUTGENERATOR_H

#include <vector>
typedef std::vector< std::pair<int, int> > JobResourceTimePairs; 

class InputGenerator {

public:
  InputGenerator(int num_compute_nodes, int max_res_per_node, 
                 int max_jobs_per_timestep, int max_time_per_job) : 
                 mNumComputeNodes(num_compute_nodes), 
                 mMaxResourcesPerNode(max_res_per_node),
                 mMaxJobsPerTimestep(max_jobs_per_timestep),
                 mMaxTimePerJob(max_time_per_job) {}

  ~InputGenerator() {}


  JobResourceTimePairs* generateJobs();


private:

  int mNumComputeNodes;
  int mMaxResourcesPerNode;
  int mMaxJobsPerTimestep;
  int mMaxTimePerJob;
};

#endif /*INPUTGENERATOR_H*/
