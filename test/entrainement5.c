#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

void *fuel_filling(void *arg)
{

}
void *car(void *arg)
{

}

int main(int ac, char **av)
{
    pthread_t th[2];
    int i = 0;
    while (i < 2)
    {
        if (i == 1)
        {
            if (pthread_create(&th[i],NULL,&fuel_filling, NULL) != 0)
            {
                perror("failed to create thread\n");
            }
        }
        else
        {
            if (pthread_create(&th[i], NULL, &car, NULL) != 0)
            {
                perror("failed to create thread");
            }
        }
        i ++;
    }
    i = 0;
    while (i<2)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("failed to join thread");
        }
    }

    return 0;
}