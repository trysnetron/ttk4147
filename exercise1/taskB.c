#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <x86intrin.h>


#define LATENCY_REPS 1000000


int main(void)
{
    double total_time = 0;
    unsigned long long last_time = __rdtsc();
    unsigned long long now;    
    for (int i=0; i<LATENCY_REPS; i++)
    {
        now = __rdtsc();
        total_time += now - last_time;
        last_time = now;
    }
    printf("Average latency for __rdtsc(): %f clock cycles\n", total_time / LATENCY_REPS);

    struct timespec now_2;
    struct timespec last_time_2;
    clock_gettime(CLOCK_MONOTONIC, &last_time_2);
    total_time = 0;
    for (int i=0; i<LATENCY_REPS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &now_2);
        total_time += now_2.tv_sec - last_time_2.tv_sec;
        last_time_2 = now_2;
    }
    printf("Average latency for clock_gettime(): %f clock cycles\n", total_time / LATENCY_REPS);

    return 0;
}