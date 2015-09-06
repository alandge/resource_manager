/* Job.cpp
 *
 */

#include "Job.h"
#include <iostream>

using namespace std;

void Job::updateTime() {
  if (mExecutionTime++ == mDuration) {
    mStatus = EXECUTED;
  }
}

