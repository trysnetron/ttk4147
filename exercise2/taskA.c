#include <pthread.h> 
#include <stdio.h>

long global = 0;
// Note the argument and return types: void*
void* fn(void* args)
{     
    long local = 0;
    for (long i = 0; i < 50000; i++) 
    {
        local++;
        global++;
    }
    printf("local %ld\n", local);
    return NULL;
} 
int main(){     
    pthread_t threadHandle;
    pthread_create(&threadHandle, NULL, fn, NULL);
    fn(NULL);
    pthread_join(threadHandle, NULL);
    printf("global %ld\n", global);
    
    return 0;
}