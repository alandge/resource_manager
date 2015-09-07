/* Job.cpp
 *
 */

#include "Job.h"
#include <iostream>
#include <cassert>

using namespace std;


Job::Job(int id, int num_resources, int duration) { 
      mId = id;
      mNumResources = num_resources;
      mDuration =duration;
      mExecutionTime = 0;
      mWaitTime = 0;
      mStatus = QUEUED;
}



void Job::updateTime() {

  assert(mExecutionTime <= mDuration);
  if (mExecutionTime == mDuration) {
    mStatus = COMPLETED;
  }
  else {
    mExecutionTime++;
  }
}

