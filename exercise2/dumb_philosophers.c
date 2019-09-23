#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SEATS 5 // How many philosophers and forks are at the table

#define HUNGRYNESS 1000 // How many times each philosopher will eat spaghetti

struct Philosopher {
    unsigned id;
    pthread_mutex_t* right_fork;
    pthread_mutex_t* left_fork;
};

void* philosophize(void* philosopher) 
{
    printf("[ %u ] I have right fork %p and left fork %p\n", 
        ((struct Philosopher*)philosopher)->id,
        ((struct Philosopher*)philosopher)->right_fork,
        ((struct Philosopher*)philosopher)->left_fork);

    for (int i = 0; i < HUNGRYNESS; i++)
    {
        // Thinks
        pthread_mutex_lock(((struct Philosopher*)philosopher)->right_fork);
        printf("[ %u ] Picked up right fork\n", ((struct Philosopher*)philosopher)->id);
        pthread_mutex_lock(((struct Philosopher*)philosopher)->left_fork);
        printf("[ %u ] Picked up left fork\n", ((struct Philosopher*)philosopher)->id);
        // Eats spaghetti
        pthread_mutex_unlock(((struct Philosopher*)philosopher)->right_fork);
        pthread_mutex_unlock(((struct Philosopher*)philosopher)->left_fork);
        printf("[ %u ] Returned forks\n", ((struct Philosopher*)philosopher)->id);
    }

    return NULL;
}

int main() 
{
    printf("yaa\n");

    pthread_t philosophers[SEATS];
    pthread_mutex_t forks[SEATS];

    // Initialize forks (mutexes)
    for (int i = 0; i < SEATS; i++)
    {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Initialize philosophers (threads)
    for (int i = 0; i < SEATS; i++)
    {
        struct Philosopher* philosopher;
        philosopher = malloc(sizeof(struct Philosopher));
        philosopher->id = i;
        philosopher->right_fork = &forks[i];
        philosopher->left_fork = &forks[(i + 1 == SEATS) ? 0 : i + 1];  

        // Make the philosopher philosophize and assign him Philosopher
        pthread_create(&philosophers[i], NULL, philosophize, philosopher);
    }

    // Deinitialize philosophers
    for (int i = 0; i < SEATS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Deinitialize forks
    for (int i = 0; i < SEATS; i++)
    {
        pthread_mutex_destroy(&forks[i]);
    }

    printf("All pholosophers have eaten and thought. Nice!\n");

    return 0;
}