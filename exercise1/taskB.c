#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <x86intrin.h>


#define LATENCY_REPS 10000000


int main(void)
{
    double total_time = 0;
    unsigned long long start = __rdtsc();
    
    for (int i=0; i<LATENCY_REPS; i++)
    {
        __rdtsc();
    }
    unsigned long long stop = __rdtsc();

    printf("Average latency for __rdtsc(): %f clock cycles\n", (double)(stop - start) / LATENCY_REPS);



    struct timespec dummy;
    start = __rdtsc();
    for (int i=0; i<LATENCY_REPS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &dummy);
    }
    stop = __rdtsc();

    printf("Average latency for clock_gettime(): %f clock cycles\n", (double)(stop - start) / LATENCY_REPS);


    struct tms dummy_2;
    start = __rdtsc();
    for (int i=0; i<LATENCY_REPS; i++) times(&dummy_2);
    stop = __rdtsc();

    printf("Average latency for times(): %f clock cycles\n", (double)(stop - start) / LATENCY_REPS);


    return 0;
}