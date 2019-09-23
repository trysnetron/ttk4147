#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SEATS 5 // How many philosophers and forks are at the table

#define HUNGRYNESS 1000 // How many times each philosopher will eat spaghetti

struct Philosopher {
    unsigned id;
    pthread_mutex_t* right_fork;
    int right_fork_order;
    pthread_mutex_t* left_fork;
    int left_fork_order;
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
        if (((struct Philosopher*)philosopher)->right_fork_order < ((struct Philosopher*)philosopher)->left_fork_order)
        {
            // Pick up right fork first
            pthread_mutex_lock(((struct Philosopher*)philosopher)->right_fork);
            printf("[ %u ] Picked up right fork\n", ((struct Philosopher*)philosopher)->id);
            pthread_mutex_lock(((struct Philosopher*)philosopher)->left_fork);
            printf("[ %u ] Picked up left fork\n", ((struct Philosopher*)philosopher)->id);
        }
        else
        {
            // Pick up left fork first
            pthread_mutex_lock(((struct Philosopher*)philosopher)->left_fork);
            printf("[ %u ] Picked up left fork\n", ((struct Philosopher*)philosopher)->id);
            pthread_mutex_lock(((struct Philosopher*)philosopher)->right_fork);
            printf("[ %u ] Picked up right fork\n", ((struct Philosopher*)philosopher)->id);
        }
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
        int right = i;
        int left = (i + 1 == SEATS) ? 0 : i + 1;
        philosopher->right_fork = &forks[right];
        philosopher->right_fork_order = right;        
        philosopher->left_fork = &forks[left];  
        philosopher->left_fork_order = left;  

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