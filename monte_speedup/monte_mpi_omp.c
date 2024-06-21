#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    clock_t start_time = clock();
    int my_rank, comm_sz;
    double pi_estimate;
    long long int total_tosses;

    if (argc > 1)
    {
        total_tosses = atoll(argv[1]);
    }
    else
    {
        total_tosses = 10000000000;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int number_of_threads = 8;
    omp_set_num_threads(number_of_threads);

    long long int tosses_per_process = total_tosses / comm_sz;
    long long int total_in_circle_per_process = 0;

#pragma omp parallel reduction(+ : total_in_circle_per_process)
    {
        unsigned int seed = omp_get_thread_num();
#pragma omp for
        for (long long int toss = 0; toss < tosses_per_process; toss++)
        {
            double x = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;
            double y = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;
            double distance_squared = x * x + y * y;
            if (distance_squared <= 1)
                total_in_circle_per_process++;
        }
    }

    long long int total_in_circle;
    MPI_Reduce(&total_in_circle_per_process, &total_in_circle, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        double num = 4 * total_in_circle;
        double den = (double)total_tosses;
        pi_estimate = num / den;
        printf("Using omp and mpi\n")
        printf("Pi estimated with %lld tosses: %f\n", total_tosses, pi_estimate);

        clock_t end_time = clock();
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Time elapsed: %f seconds\n", elapsed_time);
    }

    MPI_Finalize();

    return 0;
}