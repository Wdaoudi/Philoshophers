/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:17:17 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/26 11:35:01 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_list_philo(t_monitor *monitor)
{
	t_philo	*current;

	printf("philo id = %d\n", monitor->first->id);
	if (monitor->first->next)
	{
		current = monitor->first->next;
		while (current)
		{
			printf("philo id = %d\n", current->id);
			current = current->next;
		}
	}
	printf("End of the list\n");
}

void	ft_free_all(t_monitor *monitor)
{
	t_philo	*current;
	t_philo	*next;

	if (monitor->first)
	{
		current = monitor->first;
		while (current)
		{
			next = current->next;
			pthread_mutex_destroy(&current->fork);
			free(current);
			current = next;
		}
	}
	pthread_mutex_destroy(&monitor->die);
	pthread_mutex_destroy(&monitor->print);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (write(2, "gettimeofday() error\n", 22), 0);
	// printf("time is %ld \n", (time.tv_sec * 1000) + time.tv_usec);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); // milliseconde
															// retourne le resultat en milliseconde
}

t_state	ft_usleep(t_philo *philo, long time /*en milliseconde*/)
{
	long	starting_time;
	long	actual_time;

	starting_time = get_current_time(); // miliseconde
	actual_time = get_current_time();   // milliseconde
	while ((actual_time - starting_time) < time)
	{
		if (check_if_dead(philo) == FINISH)
			return (FINISH);
		usleep(100); // en useconde
		actual_time = get_current_time();
	}
	return (CONTINUE);
}
