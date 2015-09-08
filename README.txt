
Author: Aaditya G. Landge
aadityalandge@gmail.com

Project for Mesosphere:

A simulator for cluster job scheduling has been implemented. The simulator takes
in the following parameters as input:
Input:
-----
1. Number of time steps : Duration of the simulation
2. Number of nodes in the cluster
3. Number of resources per node in the cluster
4. Maximum duration of a job
5. Maximum time steps in between input jobs that are submitted
6. Mode: The scheduling algorithm to be used
    0 - First Come First Serve (fcfs)
    1 - Firt Fit Decreasing (FFD) with a max wait time
7. Max Job Wait Time if Mode=1


Output:
------

Gives a trace the jobs being input and the scheduling queues as well as cluster
state for each timestep.
When simulation is over prints some statistics:
Eg:
Simulation Complete... 
Total Input Jobs: 326
Total Completed Jobs: 111
Mean Job Wait Time: 144.291
Mean Cluster Utilization(%) : 93.6444


Constraints on input:
--------------------
- Each job can reside on only a single node
- A job can be scheduled only if all resources requested by it are available
- Size of the cluster cannot be changed dynamically


Overview:
--------

1. Simulator: 
  Manages the time steps and keeps updating the system.
  Contains the following:
  - Input Generator
  - Compute Cluster
  - Scheduler

2. InputGenerator:
  Randomly generates jobs of random duration and requiring random resources. 
  Made use of C++11 <random> which allows a wide choice of random distributions.
  I have used uniform distribution, but the code can be easily modified to use
  other distributions to model real life scenarios.

3. Compute Cluster:
  Has a collection of Compute Nodes.

4. Schedular (Abstract Base class):
  Takes in jobs and provides on which node they should be assigned. 
  Derived classes :
  - FcfsSchedular
  - FFDSchedular with max wait time
    Uses a priority queue for the jobs based on the number of resources required
    for the job. Does a first fit for the jobs in this queue. If no fit exists,
    picks next job from the queue. To avoid starvation, uses a separate queue
    for jobs that have reached the "max wait time". Jobs in this queue are given
    priority. The input parameter for "max wait time" affects the behavior of
    the scheduling.
    
All the above classes are defined in include and src folder.
  

Build Instruction:
------------------
On the top level directory:

make all

Execution Instructions:
-----------------------

./run_simular <list of input parameters>

Giving no input parameters will display the usage of the utility.


Future Ideas and Features:
More Ideas that can be implemented:

1. Input Simulation:

   The framework has a the ability to pick the distribution for the random
   number generators that can allow us to simulate various real world job
   request distributions. The basic implementation uses the uniform distribution
   to generate jobs, but real world scenarios can be modelled using different
   distributions (eg. exponential).

2. Changing Input Constraints:
   - Elastic jobs
   We can consider the jobs to be elastic in the sense that jobs can start
   execution even if all resources are not available and the schedular should
   incrementally provide more resources to the job as and when they are
   available
   - Job Preemption

3. Scheduling Algorithm:
  
   There are several scheduling algorithms proposed in the literature. The
   choice of the scheduling algorithm is really driven by the constraints and
   circumstances of the scenario. I have implemented a monolithic scheduling
   framework.

4. Collection of statistics:

  a) Job Statistics: To understand distribution of jobs which can be fed to the
  scheduling algo for taking decisions tuned to the job workload

  b) Node Statistics: Per node utilization over time or aggregate over certain
  time period

  c) Cluster Statistics: Cluster level statistics aggregated over all the nodes
  in the cluster. Again can be done per time step or over a period of time. Can
  be used to get an understanding of the behavior of the scheduling algorithm

  d) Scheduling Algorithm Statistics: length of the jobQ at any given time or
  average over a period of time. Time taken to make a decision on scheduling to
  get the efficiency of the algorithm.
  "max wait time" - the value of this parameter can be determined by running
  multiple experiments with different values and studying its behavior with
  respect to "Mean Job Wait Time" or cluster utilization.


  The above can be written to files. In a real world situation every node would
  be storing this information to the file system or we can explore ways in which
  this information can be aggregated before writing to file to reduce overhead
  added to the system. We can explore better formats for
  storage, retrieval and analysis of this data. 

  Also, the above statistics is not an exhaustive list and many more statistics
  or performance metrics can be extracted from the cluster at various levels
  ranging from hardware performance metrics (eg. cycles spent in every function,
  application, cache behaviours, etc.) to more application specific metrics in
  terms requirements and actual utilization of cluster resources. These metrics
  can be exploited to identify potential optimization strategies in terms of
  performance, utilization, power optimization, etc.


