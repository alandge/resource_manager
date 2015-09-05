/*Simulator.cpp 
 *
 * Simulator for the resource manager
 *
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "Simulator.h"

using namespace std;

void Simulator::initialize(int num_timesteps, int time_delay, 
                           InputGenerator* inp_gen ) {
  
  mNumTimesteps = num_timesteps;
  mTimeDelay = time_delay;
  mInputGen = inp_gen;
  
}

void Simulator::run() {

  for (int i=0; i<mNumTimesteps; i++) {

    vector< pair<int, int> > jobs = mInputGen->generateJobs();

    cout << "Time : " << i+1 << "  :: ";
    for (int j=0; j<jobs.size(); j++ ) {
      cout << "("<< jobs[j].first << ", " << jobs[j].second << ")  ";
    }

    cout << "\n";
    this_thread::sleep_for(std::chrono::seconds(mTimeDelay));
  }


}
