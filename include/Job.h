/* Job.h
 *
 * class for a job
 *
 */

#ifndef JOB_H
#define JOB_H

typedef int JobId_t;

enum{ QUEUED = 0, RUNNING, COMPLETED};

class Job{
public:

  Job(int id, int num_resources, int duration);

  ~Job() {}

  int id() { return mId; }

  //! set the status to running, queued or executed
  void status(int state) { mStatus = state; } 

  // status of the job
  int status() {return mStatus;}

  int timeRemaining() {return mDuration - mExecutionTime; }

  int duration() { return mDuration; }

  void updateTime();

  int numResources() { return mNumResources; }

private:

  JobId_t mId;
  int mNumResources;
  int mDuration;
  int mExecutionTime;
  int mStatus;


};

#endif /*JOB_H*/
