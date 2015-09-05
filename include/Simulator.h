/*Simulator.h 
 *
 * Simulator for the resource manager
 *
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "InputGenerator.h"

class Simulator {
  public:
  Simulator() {}
  ~Simulator() {}

  void initialize(int num_timesteps, int time_delay, InputGenerator* inp_gen);

  void run();

private:
  int mNumTimesteps;
  int mTimeDelay;
  InputGenerator* mInputGen;
};


#endif /*SIMULATOR_H*/

