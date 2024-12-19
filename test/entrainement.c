#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int x = 2;

// void	*routine(void)
// {
//     x++;
// 	sleep(2);
// 	printf("value of x: %d\n",x);
// }
// void	*routine2(void)
// {
// 	sleep(2);
// 	printf("value of x: %d\n",x);
// }

int mail = 0;
pthread_mutex_t mutex; //lock

void *routine()
{
    for (int i = 0; i< 1000; i++)
        {
            pthread_mutex_lock(&mutex);
            mail++;
            pthread_mutex_unlock(&mutex);
        }
        // read mails
        //incremente ensuite 
        // puis le reecrire dans la memoire 

}

int	main(int ac, char **av)
{
	pthread_t th[4];
    int i = 0;
    // pthread create return un int, si != 0 alors echec de la creation du threads
    pthread_mutex_init(&mutex,NULL);
    while (i < 4)
    {
	    if (pthread_create(th + i, NULL, &routine, NULL) != 0)
        {
            perror("failed to create thread\n");
            return (1);
        }
        printf("thread %d has start\n",i);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        if (pthread_join(th[i], NULL) != 0)
            return 2;
        printf("thread %d has finish\n",i);
        i ++;
    }
    pthread_mutex_destroy(&mutex);
    printf("%d\n",mail);
	return (0);
}

/*
thread : partage la memoire exemple d incrementation des x par opposition avec les processes qui ont des memoires differntes
attention a la gestion de la memoire

pthread_join equivalent a un waitpid;

race condition: en cas d emploi de plusieurs threads , car l execution d une fonction simple comme incrementee une vaariable 
se divise en plusieurs etapes:
read mails, incremente, write
quand un thread s incremente trop le suivant se perd et peu se lancer avant que le premier se fini (d ou l interer des mutex )
 et s incremente mal d ou les corruptions de donnees tres grave

les mutex: doivent etre initialiser via pthread_mutex_init(&mutex) et destroy via pthread_mutex_destroy(&mutex)
ils doivent etre lock et unlock via pthread_mutex_lock/unlock(&mutex); permet d eviter les race condition 

ne pas mettre dans la meme boucle pthread create et pthread join car il va wait avant de creer les suivants ce qui
entraine une creation sequentiel et pas simultane : creation 0 finish 0 creation 1 finish 1 ... alors qu il devrait creer tout
puis join ensuite. faire deux boucles

*/