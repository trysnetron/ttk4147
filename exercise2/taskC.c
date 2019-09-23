#include <pthread.h> 
#include <stdio.h>
#include <semaphore.h>

long global = 0;
sem_t sema;
// Note the argument and return types: void*
void* fn(void* args)
{   
    long local = 0;
    for (long i = 0; i < 50000; i++) 
    {
        local++;
        sem_wait(&sema);
        global++;
        sem_post(&sema);
    }
    printf("local %ld\n", local);
    return NULL;
} 
int main(){
    sem_init(&sema, 0, 1);     
    pthread_t threadHandle;
    pthread_create(&threadHandle, NULL, fn, NULL);
    fn(NULL);
    pthread_join(threadHandle, NULL);
    printf("global %ld\n", global);
    
    return 0;
}