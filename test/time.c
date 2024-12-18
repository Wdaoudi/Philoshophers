#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(void)
{
	time_t start_time;
	time_t end_time;
	time_t time;

	start_time = get_time_in_ms();
	end_time = start_time + 2000;
	time = get_time_in_ms();
	printf("Time in ms = %ld. Time since start = %ld\n", time, time
		- start_time);
	while (get_time_in_ms() < end_time)
	{
		if (usleep(100 * 1000) == 0) // Suspend for 100 milliseconds
		{
			time = get_time_in_ms();
			printf("Time in ms = %ld. Time since start = %ld\n", time, time
				- start_time);
		}
	}
	return (0);
}

// interrompre usleep

void	philo_sleep(t_table *table, time_t sleep_time)
{
	// Variable to measure when the philosopher thread must resume:
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
        // Loop as long as it's not wake up time:
	while (get_time_in_ms() < wake_up)
	{
		// Check if the simulation has stopped. If it has,
		// stop the loop (and this function) immediately
		// to continue thread execution:
		if (has_simulation_stopped(table))
			break ;
		// If the simulation is still going, usleep for a short time:
		usleep(100);
	}
}