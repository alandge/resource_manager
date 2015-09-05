/* job.h
 *
 * class for a job
 *
 */

#ifndef JOB_H
#define JOB_H

class job{
public:

  job() {}
  ~job() {}

  // status of the job
  status() {return mStatus};

private:

  int mId;
  int mReqResource;
  int mReqTime;
  int mStatus;


};

#endif /*JOB_H*/
