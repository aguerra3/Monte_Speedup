#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
int main(int argc, char *argv[])
{
    clock_t start_time = clock();
    int number_of_threads = 8;

    long long int total_tosses;
    if (argc > 1)
    {
        total_tosses = atoll(argv[1]);
    }
    else
    {
        total_tosses = 10000000000;
    }

    long long int total_in_circle = 0;

    omp_set_num_threads(number_of_threads);

#pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        long long int number_in_circle = 0;

#pragma omp for reduction(+ : total_in_circle)
        for (long long int toss = 0; toss < total_tosses; toss++)
        {
            double x = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;
            double y = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;
            double distance_squared = x * x + y * y;
            if (distance_squared <= 1)
                total_in_circle++;
        }
    }
    double num = 4 * total_in_circle;
    double den = (double)total_tosses;
    double pi_estimate = num / den;
    printf("Using omp \n");
    printf("Pi estimated with %lld tosses: %f\n", total_tosses, pi_estimate);
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f seconds\n", elapsed_time);

    return 0;
}