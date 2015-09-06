/* Job.h
 *
 * class for a job
 *
 */

#ifndef JOB_H
#define JOB_H

enum{ QUEUED = 0, RUNNING, EXECUTED};

class Job{
public:

  Job() {}
  ~Job() {}

  //! set the status to running, queued or executed
  void status(int state) { mStatus = state; } 

  // status of the job
  int status() {return mStatus;}

  int timeRemaining() {return mDuration - mExecutionTime; }

  int duration() { return mDuration; }

  void updateTime();

  int numResources() { return mNumResources; }

private:

  int mId;
  int mNumResources;
  int mDuration;
  int mExecutionTime;
  int mStatus;


};

#endif /*JOB_H*/
