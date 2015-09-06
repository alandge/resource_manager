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
std::vector< std::pair<int, int> > InputGenerator::generateJobs() {

  std::vector < std::pair<int, int> > jobs;

  // Randomly generate number of jobs for this timestep
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  std::uniform_int_distribution<int> jobs_dist(0,mMaxJobsPerTimestep);
  std::uniform_int_distribution<int> resource_dist(1,mMaxResourcesPerNode);
  std::uniform_int_distribution<int> time_dist(1,mMaxTimePerJob);

  int num_jobs = jobs_dist(generator);

  for (int i=0; i<num_jobs; i++) {
    
    // randomly generate number of compute resources for this job
    int resources = resource_dist(generator);//rand() % mMaxResourcesPerNode + 1;

    // randomly generate time required for this job
    int job_time = time_dist(generator);//rand() % mMaxTimePerJob + 1;

    jobs.push_back(std::pair<int, int> (resources, job_time));
  }

  return jobs;
}
