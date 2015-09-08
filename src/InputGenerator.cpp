/* InputGenerator.cpp
 *
 * Generates the input stream in terms of tuples of available resources and the
 * job requests
 *
 */

#include <iostream>
#include <random>
#include "InputGenerator.h"


//! Generate a vector of job tuples (resources, timesteps) when invoked
// can extend this api to select different distributions for jobs, time and
// resources
JobResourceTimePair InputGenerator::generateJob(std::default_random_engine generator) {

  JobResourceTimePair job;

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  std::uniform_int_distribution<int> resource_dist(1,mMaxResourcesPerNode);
  std::uniform_int_distribution<int> time_dist(1,mMaxTimePerJob);
    
  // randomly generate number of compute resources for this job
  job.first = resource_dist(generator);

  // randomly generate time required for this job
  job.second = time_dist(generator);

  return job;
}
