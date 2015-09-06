/*Simulator.cpp 
 *
 * Simulator for the resource manager
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "Simulator.h"

void Simulator::initialize(int num_timesteps, int time_delay, 
                           InputGenerator* inp_gen,
                           ComputeCluster* cluster, 
                           Scheduler* scheduler) {
  
  mNumTimesteps = num_timesteps;
  mTimeDelay = time_delay;
  mInputGen = inp_gen;
  mCluster = cluster;
  mScheduler = scheduler;
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

  int job_count = 0;
  int max_jobs = 8;
  //for (int i=0; i<mNumTimesteps; i++) {
  for (int i=0; ; i++) {


    std::cout << "Time : " << i+1 << "\n";
    std::vector<Job*> new_jobs;

    if (job_count < max_jobs) {
      JobResourceTimePairs* job_time_pairs = mInputGen->generateJobs();
      JobResourceTimePairs::iterator j_it;

      std::cout << "Input Jobs :: ";
      for (j_it=job_time_pairs->begin(); j_it != job_time_pairs->end(); j_it++ ) {
        
        Job* job = new Job(job_count++,  j_it->first,  j_it->second);
        mJobs.push_back(job);
        new_jobs.push_back(job);

        std::cout << "(" << j_it->first << ", " << j_it->second << ")  ";
      }

      delete job_time_pairs;
      std::cout << "\n";
    }

    NodeResourcePairs* cluster_state = mCluster->updateState(); 
    NodeResourcePairs::iterator it;

    std::cout << "Cluster State :: ";
    mCluster->printClusterState();
    //for (it=cluster_state->begin(); it!=cluster_state->end(); it++) {
    //  std::cout << "("  << it->first 
    //            << ", " << it->second << ")  ";
    //}

    //std::cout << "\n\n";

    // Schedule jobs
    NodeJobPairs* scheduled_jobs = mScheduler->getScheduledJobs(new_jobs, 
                                                                cluster_state);
    NodeJobPairs::iterator sj_it;
    std::cout << "Scheduled Jobs (NodeId, JobId) :: ";
    for (sj_it=scheduled_jobs->begin(); sj_it!=scheduled_jobs->end(); sj_it++) {
      std::cout << "("  << sj_it->first 
                << ", " << sj_it->second->id() << ")  ";
    }
    std::cout << "\n";
    mScheduler->printJobQ();

    // Run jobs
    mCluster->runJobs(scheduled_jobs);

    
    // Remove completed jobs
    RemoveCompletedJobs();


    delete cluster_state;
    delete scheduled_jobs;


    std::this_thread::sleep_for(std::chrono::seconds(mTimeDelay));
  }

}



