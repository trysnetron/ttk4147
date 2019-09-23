#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/times.h>

void print_help(void)
{
    printf("Usage: taskA [number]\n");
    printf("\tNumber can beone of the following\n");
    printf("\t0: sleep()\n");
    printf("\t1: busy_wait() with get_clocktime\n");
    printf("\t2: busy_wait() with times()\n");
}

struct timespec timespec_normalized(time_t sec, long nsec)
{     
    while(nsec >= 1000000000)
    {         
        nsec -= 1000000000;         
        ++sec;     
    }     
    while(nsec < 0)
    {         
        nsec += 1000000000;
        --sec;     
    }     
    return (struct timespec){sec, nsec}; 
} 

struct timespec timespec_sub(struct timespec lhs, struct timespec rhs)
{     
    return timespec_normalized(lhs.tv_sec - rhs.tv_sec, lhs.tv_nsec - rhs.tv_nsec); 
} 

struct timespec timespec_add(struct timespec lhs, struct timespec rhs)
{     
    return timespec_normalized(lhs.tv_sec + rhs.tv_sec, lhs.tv_nsec + rhs.tv_nsec); 
} 

int timespec_cmp(struct timespec lhs, struct timespec rhs)
{     
    if (lhs.tv_sec < rhs.tv_sec) return -1;     
    if (lhs.tv_sec > rhs.tv_sec) return 1;     
    return lhs.tv_nsec - rhs.tv_nsec; 
}

void busy_wait_clock_gettime(struct timespec t)
{     
    struct timespec now;     
    clock_gettime(CLOCK_MONOTONIC, &now);     
    struct timespec then = timespec_add(now, t);     
    while(timespec_cmp(now, then) < 0)
    {         
        for(int i = 0; i < 10000; i++) {}         
        clock_gettime(CLOCK_MONOTONIC, &now);     
    } 
}

void busy_wait_times(unsigned int seconds) 
{
    struct tms times_buffer;
    times(&times_buffer);
    while (times_buffer.tms_utime < sysconf(_SC_CLK_TCK) * seconds)
    {
        for(int i = 0; i < 10000; i++) {}         
        times(&times_buffer);
    }    
}

int main(int argc, char **argv) 
{
    if (argc > 2) {
        printf("[ERROR] taskA only takes one argument\n");
        print_help();
        return 1;
    }
    if (argc < 2) {
        printf("[ERROR] taskA needs one argument\n");
        print_help();
        return 1;
    }

    
    switch (argv[1][0])
    {
    case '0':
        sleep(1);
        break;

    case '1':
        ;
        struct timespec delay = { .tv_sec=1, .tv_nsec=0 };
        busy_wait_clock_gettime(delay);
        break;
    case '2':
        busy_wait_times(1);

    default:
        printf("[ERROR] Unsupported argument\n");
        return 2;
    }
    return 0;
}