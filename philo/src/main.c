/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:52:24 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 16:13:21 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	int			i;
	t_data		data;
	t_monitor	monitor;

	i = 0;
	(void)i;
	if (ac != 6 && ac != 5)
		return (printf("Error\nInvalid number of argument\n"), 1);
	if (parsing_argument(av, &data) != 0)
		return (printf("Error\nInvalid argument\n"), 1);
	if (init_monitor(&data, &monitor) != 0)
		return (printf("Error\nCreating philosophers\n"), 1);
	if (create_philo_list(&monitor) != 0)
		return (printf("Error\nCreating philosophers\n"), 1);
	if (assign_forks(&monitor) != 0)
		return (ft_free_all(&monitor), 1);
	if (init_threads(&monitor) == 1)
		return (printf("Error\nCreating thread\n"), ft_free_all(&monitor), 1);
	ft_free_all(&monitor);
	return (0);
}

/*
timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

gettimeofday(struct timeval *tv, NULL);
return (0 si success or -1 if failed);


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
*/

/*
gerer la memoire:
 - free la liste chainee de philo
 - destroy les different mutex (4 poour le moment)*/