#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int			id;
	pthread_t	thread;
}				t_data;

void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(data->id * 10);
	printf("philo %d end his journey \n",data->id);
}

int	main(void)
{
	pthread_t th[4];
	int i = 0;
	t_data data;

    
	while (i < 4)
	{
        data.id = i;
		if (pthread_create(th + i, NULL, &routine,(void *)data) != 0)
		{
			perror("failed to initialize thread\n");
			return (1);
		}
		i++;
	}
	while (i > 0)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("failed to join thread\n");
			return (1);
		}
		i--;
	}
	return (0);
}