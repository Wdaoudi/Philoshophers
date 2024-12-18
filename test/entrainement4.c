#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutex;

void *routine(void *arg)
{
        if (pthread_mutex_trylock(&mutex) == 0)
        {    
        printf("got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
        }
        else
            printf("didn t get lock\n");
}


int	main(int ac, char **av)
{
	pthread_t th[4];
    pthread_mutex_init(&mutex,NULL);
	int i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("error creating thread");
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("error at joining thread");
		}
		i++;
	}
	return (0);
}


/*
try_lock: n attends pas comme lock qu un mutex s unlock il regarde directement si le mutex est lock ou unlock et apres il passe
a la suite

*/