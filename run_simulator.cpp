#include <cstdio>
#include <iostream>
#include "Simulator.h"
#include "InputGenerator.h"
#include "FcfsScheduler.h"
#include "FFDScheduler.h"

using namespace std;

int main(int argc, char* argv[]) {

  if (argc < 7) {
    cout << "Usage: <num timesteps> <number of nodes> <num of resources per node> <max time per job> \
      <max time between jobs> <schedular mode: FCFS = 0, FFD = 1> <max_job_wait_time>\n";
    return 0;
  }

  int num_time_steps = atoi(argv[1]);
  int num_nodes = atoi(argv[2]);
  int num_res_per_node = atoi(argv[3]);
  int max_time_per_job = atoi(argv[4]);
  int max_time_bet_jobs = atoi(argv[5]);
  int mode = atoi(argv[6]);
  int max_job_wait_time;
  
  if (argc == 8)
     max_job_wait_time = atoi(argv[7]);
  else
     max_job_wait_time = max_time_per_job*2;

  std::cout << "max wait time: " << max_job_wait_time << "\n";

  Simulator s;
  InputGenerator* inp_gen = new InputGenerator(num_nodes, num_res_per_node,
                                               max_time_per_job);
  ComputeCluster* cluster = new ComputeCluster(num_nodes, num_res_per_node);

  Scheduler* scheduler;
  if (mode == 0)
    scheduler = new FcfsScheduler();
  else
    scheduler = new FFDScheduler(max_job_wait_time);

  cout << "Num nodes: " << cluster->numNodes() << "\n";
  
  // time tick for the simulator in ms
  int time_tick = 10;
  s.initialize(num_time_steps, time_tick, max_time_bet_jobs, inp_gen, 
               cluster, scheduler);
  
  s.run();  
 
  return 0;

}
