#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
    int index = *(int*)arg;
    int sum = 0;
    int j = 0;
    while (j < 5)
    {
        sum += primes[index + j];
        j ++;
    }
    printf("local sum: %d\n",sum);
    *(int*)arg = sum;
    // printf("%d\n",primes[index]);
    return(arg);
}

int main(int ac, char **av)
{
    pthread_t th[2];
    int i = 0;
        int *a;
    while (i < 2)
    {
        a = malloc(sizeof(int));
        *a = i * 5;
        if (pthread_create(&th[i],NULL,&routine,a)!= 0)
        {
            perror("failed create");
        }
        i ++;
    }
    i = 0;
    int globalsum = 0;
    while (i < 2)
    { int *res;
        if (pthread_join(th[i],(void**)&res)!= 0)
        {
            perror("failed create");
        }
        globalsum += *res;
        free(res);
        i ++;
    }
    printf("GLobalsum : %d\n", globalsum);
    return 0;
}