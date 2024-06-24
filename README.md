# Monte_Speedup
This project involves three implementations of the Monte Carlo algorithm: one running in serial, one using MPI for parallel processing across multiple nodes, and one using OpenMP for parallel processing across multiple threads on a shared memory system. The goal is to estimate the value of pi by simulating random points in a unit square and determining the ratio of points that fall inside a quarter-circle. The run times of each implementation are compared to demonstrate the performance benefits of parallelization.

Monte Carlo Algorithm Overview
The Monte Carlo algorithm estimates pi through the following steps:

Generate random points within the unit square, ranging from zero to one in both the x and y coordinates.
Count the number of points that fall inside the quarter-circle of radius one, centered at the origin.
Use the ratio of points inside the quarter-circle to the total number of points to estimate pi.
Serial Implementation
In the serial implementation, the algorithm runs on a single processor. It generates a large number of random points, checks each point to see if it falls within the quarter-circle, and calculates the estimate of pi based on the ratio of inside points to the total number of points. The execution time is measured from start to finish.

MPI Implementation
The MPI implementation involves distributing the computation across multiple processors. Each processor generates a subset of the total points and counts how many fall inside the quarter-circle. These counts are then combined to calculate the final estimate of pi. The run time includes the time taken for all processors to complete their work and communicate their results.

OpenMP Implementation
The OpenMP implementation uses multiple threads within a shared memory system. The total number of points is divided among the threads, each of which performs the Monte Carlo simulation independently. The results from all threads are combined to produce the final estimate of pi. The execution time includes the time taken for all threads to complete their work.

Run Time Comparison
After running each implementation (serial, MPI, and OpenMP), the execution times are compared. This comparison highlights the performance improvements achieved through parallelization, demonstrating how MPI and OpenMP can significantly speed up the computation of the Monte Carlo algorithm for estimating pi.
