#include <cstdio>
#include <iostream>
#include "Simulator.h"
#include "InputGenerator.h"
#include "FcfsScheduler.h"
#include "FFDScheduler.h"

using namespace std;

int main(int argc, char* argv[]) {

 /* if (argc < 4) {
    cout << "Usage: <number of nodes> <num of resources per node> <max num of jobs per timestep> \
      <max time per job>\n";
    return 0;
  }*/

//  int num_nodes = atoi(argv[1]);
//  int num_res_per_node = atoi(argv[2]);
//  int max_job_per_timestep = atoi(argv[3]);
//  int max_time_per_job = atoi(argv[4]);
 
  Simulator s;
  InputGenerator* inp_gen = new InputGenerator(2,8,0,10);
  ComputeCluster* cluster = new ComputeCluster(2, 8);
  //Scheduler* scheduler = new FcfsScheduler();
  Scheduler* scheduler = new FFDScheduler(5);

  cout << "Num nodes: " << cluster->numNodes() << "\n";
  s.initialize(10, 1, 1, inp_gen, cluster, scheduler);
  
  s.run();  
 
  cout << "hello world\n";
  return 0;

}
