#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <x86intrin.h>
#include <string.h>

#define RESOLUTION_REPS 1000000

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("lol nope\n");
        return 1;
    }

    int ns_max = 100; 
    unsigned long long histogram[ns_max];
    memset(histogram, 0, sizeof(unsigned long long)*ns_max);
    
    if (argv[1][0] == '1') {
        unsigned long long t1;    
        unsigned long long t2;     
        unsigned long long ns;     
            
        for(int i = 0; i < RESOLUTION_REPS; i++){     
            t1 = __rdtsc();    
            t2 = __rdtsc();     
            ns = (t2 - t1);     
            if (ns >= 0 && ns < ns_max) {         
                histogram[ns]++;
            } 
        } 
    } else if (argv[1][0] == '2') {
        struct timespec t1;    
        struct timespec t2;     
        unsigned long long ns;     
            
        for(int i = 0; i < RESOLUTION_REPS; i++){     
            clock_gettime(CLOCK_MONOTONIC, &t1);    
            clock_gettime(CLOCK_MONOTONIC, &t2);     
            ns = (t2.tv_nsec - t1.tv_nsec);     
            if (ns >= 0 && ns < ns_max) {         
                histogram[ns]++;
            } 
        }
    } else if (argv[1][0] == '3') {
        struct tms t1;    
        struct tms t2;     
        unsigned long long ns;     
            
        for(int i = 0; i < RESOLUTION_REPS; i++){     
            times(&t1);    
            times(&t2);     
            ns = (t2.tms_utime - t1.tms_utime);     
            if (ns >= 0 && ns < ns_max) {         
                histogram[ns]++;
            } 
        }
    }  
    for(int i = 0; i < ns_max; i++)
    {     
        printf("%lld\n", histogram[i]);
    } 
    return 0;
}