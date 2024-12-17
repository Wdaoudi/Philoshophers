#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void *roll_dice()
{
    int value = (rand() % 6) +1;
    int *result = malloc(sizeof(int));
    // printf("%d\n",value);
printf("%p\n",result);
    *result = value;
    return (void *)result;
}

int	main(int ac, char **av)
{
    int *res;
    srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
		return (1);
	if (pthread_join(th, (void **) &res)!= 0)
	{
		return (2);
	}
    printf("main:%p\n",res);
    printf("%d\n",*res);
    free(res);
	return (0);
}