#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    clock_t start_time = clock();
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
    unsigned int seed = 1; 

    double x;
    double y;
    double distance_squared;
    for (long long int toss = 0; toss < total_tosses; toss++) {
        // double x = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;
        // double y = (double)rand_r(&seed) / (double)RAND_MAX * 2 - 1;

        double x = (double)rand() / (double)RAND_MAX * 2 - 1;
        double y = (double)rand() / (double)RAND_MAX * 2 - 1;
        distance_squared = x*x + y*y;
        if (distance_squared <= 1) total_in_circle++;
    }

    double num = 4 * total_in_circle;
    double den = (double)total_tosses;
    double pi_estimate = num / den;
    printf("Using serial code\n");
    printf("Pi estimated with %lld tosses: %f\n", total_tosses, pi_estimate);
    clock_t end_time = clock();
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time elapsed: %f seconds\n", elapsed_time);
    return 0;
}