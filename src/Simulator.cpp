/*Simulator.cpp   
 *
 * Simulator for the resource manager
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "Simulator.h"

void Simulator::initialize(int num_timesteps, int time_delay, 
                           int max_time_between_jobs, 
                           InputGenerator* inp_gen,
                           ComputeCluster* cluster, 
                           Scheduler* scheduler) {
  
  mNumTimesteps = num_timesteps;
  mTimeDelay = time_delay;
  mMaxTimeBetweenJobs = max_time_between_jobs;
  mInputGen = inp_gen;
  mCluster = cluster;
  mScheduler = scheduler;

  int job_count = 0;
  NodeJobPairs initial_jobs;
  NodeResourcePairs cluster_state;

  int num_resources_per_node = mCluster->numResourcesPerNode();

  for (int i=0; i<mCluster->numNodes(); i++) {
    JobResourceTimePair job_time_pair = mInputGen->generateJob();
    
    Job* job = new Job(job_count++, job_time_pair.first, job_time_pair.second);

    initial_jobs.push_back(std::pair<int, Job*>(i, job));
    cluster_state.push_back(
        std::pair<int, int>(i, num_resources_per_node - job->numResources()));
  }

  mCluster->runJobs(&initial_jobs);

  mScheduler->initialize(mCluster->numNodes(), &cluster_state);

  std::cout << "Initial Cluster State (nodeId, avail_res) :: ";
  mCluster->printClusterState();
}


void Simulator::RemoveCompletedJobs() {

  std::list<Job*>::iterator it=mJobs.begin();

  while (it!=mJobs.end()) {
    if ((*it)->status() == COMPLETED) {
      mJobs.erase(it++);
    }
    it++;
  }
}


void Simulator::run() {

  int job_count = mCluster->numNodes();
  int max_jobs = 8;

  // generate seed for random number generation
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> time_dist(1,mMaxTimeBetweenJobs);
  int time_between_jobs =1;

  //for (int i=0; i<mNumTimesteps; i++) {
  for (int i=0; ; i++) {

    std::cout << "\nTime : " << i+1 ;
    std::vector<Job*> new_jobs;
    
    if ((--time_between_jobs == 0) && (job_count < max_jobs)) {
      JobResourceTimePair job_time_pair = mInputGen->generateJob();

      std::cout << "\nInput Job (jobId, resources, time):: ";
            
      Job* job = new Job(job_count++, job_time_pair.first, job_time_pair.second);
      mJobs.push_back(job);
      new_jobs.push_back(job);

      std::cout << "(" << job->id() << ", " << job->numResources() 
                << ", " << job->duration() << ")  ";

      // randomly generate time delay in between input jobs

      time_between_jobs = time_dist(generator);
    }
    //else {
      //time_between_jobs--;
    //}

    std::cout << "\n";

    NodeResourcePairs* cluster_state = mCluster->updateState(); 
    NodeResourcePairs::iterator it;

    std::cout << "Cluster State (nodeId, avail_res) :: ";
    mCluster->printClusterState();

   // for (it=cluster_state->begin(); it!=cluster_state->end(); it++) {
   //   std::cout << "("  << it->first 
   //             << ", " << it->second << ")  ";
   // }

   // std::cout << "\n\n";

   
    // Schedule jobs
    NodeJobPairs* scheduled_jobs = mScheduler->getScheduledJobs(new_jobs, 
                                                                cluster_state);
    NodeJobPairs::iterator sj_it;
    std::cout << "Scheduled Jobs (nodeId, jobId) :: ";
    for (sj_it=scheduled_jobs->begin(); sj_it!=scheduled_jobs->end(); sj_it++) {
      std::cout << "("  << sj_it->first 
                << ", " << sj_it->second->id() << ")  ";
    }
    std::cout << "\n";
    //mScheduler->printJobQ();

    // Run jobs
    mCluster->runJobs(scheduled_jobs);

     std::cout << "Cluster State (nodeId, avail_res) :: ";
    mCluster->printClusterState();
        
    // Remove completed jobs
    RemoveCompletedJobs();


    delete cluster_state;
    delete scheduled_jobs;


    std::this_thread::sleep_for(std::chrono::seconds(mTimeDelay));
  }

}



