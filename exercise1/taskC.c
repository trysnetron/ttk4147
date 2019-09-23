#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>
#include <sched.h>

#define RESOLUTION_REPS 1000000

int main() {
    int ns_min = 200;
    int ns_max = 300; 
    int ns_size = ns_max - ns_min;
    unsigned long long histogram[ns_size];
    memset(histogram, 0, sizeof(unsigned long long)*ns_size);
    
    struct timespec t1;    
    struct timespec t2;     
    unsigned long long ns;     
            
    for(int i = 0; i < RESOLUTION_REPS; i++){     
        clock_gettime(CLOCK_MONOTONIC, &t1);    
        sched_yield();
        clock_gettime(CLOCK_MONOTONIC, &t2);     
        ns = (t2.tv_nsec - t1.tv_nsec);     
        if (ns >= ns_min && ns < ns_max) {         
            histogram[ns - ns_min]++;
        } 
    }

    for(int i = 0; i < ns_size; i++)
    {     
        printf("%lld\n", histogram[i]);
    } 
    return 0;
}