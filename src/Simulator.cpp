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
                           ComputeCluster* cluster ) {
  
  mNumTimesteps = num_timesteps;
  mTimeDelay = time_delay;
  mInputGen = inp_gen;
  mCluster = cluster;
}

void Simulator::run() {

  for (int i=0; i<mNumTimesteps; i++) {

    std::vector< std::pair<int, int> > jobs = mInputGen->generateJobs();

    std::cout << "Time : " << i+1 << "\n";
    std::cout << "Input Jobs :: ";
    for (int j=0; j<jobs.size(); j++ ) {
      std::cout << "("<< jobs[j].first << ", " << jobs[j].second << ")  ";
    }
    std::cout << "\n";

    std::vector< std::pair<int, int> > cluster_state = mCluster->updateState();
    
    std::cout << "Cluster State :: ";
    for (int j=0; j<cluster_state.size(); j++ ) {
      std::cout << "("<< cluster_state[j].first << ", " << cluster_state[j].second << ")  ";
    }
    std::cout << "\n\n";


    std::this_thread::sleep_for(std::chrono::seconds(mTimeDelay));
  }


}
