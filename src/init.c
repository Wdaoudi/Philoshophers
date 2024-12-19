/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:02:58 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/19 20:13:26 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	create_philo_list(t_monitor *monitor)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (i < monitor->data->philo)
	{
		new = create_philo(monitor, i);
		if (!new)
			return (ft_free_all(monitor), 1);
		add_to_list(monitor, new);
		i++;
	}
	return (0);
}
void	add_to_list(t_monitor *monitor, t_philo *new)
{
	t_philo	*current;

	if (!monitor->first)
	{
		monitor->first = new;
		return ;
	}
	else
	{
		current = monitor->first;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new;
	}
}

t_philo	*create_philo(t_monitor *monitor, int i)
{
	t_philo			*new;
	pthread_t		th;
	pthread_mutex_t	fork;

	(void)monitor;
	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	if (pthread_mutex_init(&fork, NULL) != 0)
		return (NULL);
	new->fork = fork;
	new->id = i + 1;
	new->next = NULL;
	new->number_of_meal = 0;
	new->last_meal_time = 0;
	new->starting_time = get_current_time();
	return (new);
}

int	init_monitor(t_data *data, t_monitor *monitor)
{
	pthread_mutex_t	die;
	pthread_mutex_t	print;

	monitor->data = data;
	monitor->is_die = false;
	monitor->first = NULL;
	if (pthread_mutex_init(&die, NULL) != 0 || pthread_mutex_init(&print,
			NULL) != 0)
		return (1);
	monitor->die = die;
	monitor->print = print;
	return (0);
}

void	init_threads(t_monitor *monitor)
{
	int i = 0;
	pthread_t th[monitor->data->philo];
	t_philo *current;
	
	while (i < monitor->data->philo)
	{
		if (pthread_create(th[i], NULL, &routine, NULL) != 0)
		{
			printf("failed to create thread\n");
			return (1);
		}
		monitor->first->thread = th[i];

		i++;
	}
	while (i > 0)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			return (1);
		}
		i--;
	}
}