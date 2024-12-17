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
int lock = 0;

void *routine()
{
    for (int i = 0; i< 1000; i++)
        mail++;
        // read mails
        //incremente ensuite 
        // puis le reecrire dans la memoire 

}

int	main(int ac, char **av)
{
	pthread_t t1, t2;
    // pthread create return un int si != 0 alors echec de la creation du threads

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{ // arg1 = pointeur jusqu au thread, arg2= je sais pas,arg3 = fonction, arg4 = NULL;
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0) // wait for thread arg1 = variable,arg2 = pointeur vers le resultat de retour la c est nUlll car void return (3);
        return 3;
    if (pthread_join(t2, NULL) != 0)
		return (4);
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
quand un thread s incremente trop le suivant se perd et s incremente mal d ou les corruptions de donnees tres grave
*/