/*Simulator.h 
 *
 * Simulator for the resource manager
 *
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "InputGenerator.h"
#include "ComputeCluster.h"
#include "Scheduler.h"

class Simulator {
  public:
  Simulator() {}
  ~Simulator() {}

  void initialize(int num_timesteps, int time_delay,
                  int max_time_between_jobs, InputGenerator* inp_gen,
                  ComputeCluster* cluster, Scheduler* scheduler);

  void run();

private:
  int mNumTimesteps;
  int mTimeDelay;
  int mMaxTimeBetweenJobs;
  InputGenerator* mInputGen;
  ComputeCluster* mCluster;
  Scheduler* mScheduler;
  std::list<Job*> mJobs;

  void RemoveCompletedJobs();
};


#endif /*SIMULATOR_H*/

