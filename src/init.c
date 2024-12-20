/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:02:58 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/20 12:35:48 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	add_to_list(t_monitor *monitor, t_philo *new)
{
	t_philo	*current;

	if (!monitor->first)
	{
		monitor->first = new;
		return ;
	}
	current = monitor->first;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	assign_forks(t_monitor *monitor)
{
	t_philo	*current;
	t_philo	*next;

	current = monitor->first;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = monitor->first;
		current->r_fork = &current->fork;
		current->l_fork = &next->fork;
		current = current->next;
	}
	return (0);
}

t_philo	*create_philo(t_monitor *monitor, int i)
{
	t_philo	*new;

	(void)monitor;
	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	if (pthread_mutex_init(&new->fork, NULL) != 0)
	{
		free(new);
		return (NULL);
	}
	new->id = i + 1;
	new->next = NULL;
	new->number_of_meal = 0;
	new->last_meal_time = get_current_time();
	new->starting_time = get_current_time();
	new->monitor = monitor;
	new->l_fork = NULL;
	new->r_fork = NULL;
	return (new);
}

int	create_philo_list(t_monitor *monitor)
{
	int		i;
	t_philo	*new;

	i = 0;
	while (i < monitor->data->philo)
	{
		new = create_philo(monitor, i);
		if (!new)
		{
			ft_free_all(monitor);
			return (1);
		}
		add_to_list(monitor, new);
		i++;
	}
	return (assign_forks(monitor));
}

int	init_monitor(t_data *data, t_monitor *monitor)
{
	// pthread_mutex_t	die;
	// pthread_mutex_t	print;

	monitor->data = data;
	monitor->is_die = false;
	monitor->first = NULL;
	if (pthread_mutex_init(&monitor->die, NULL) != 0
		|| pthread_mutex_init(&monitor->print, NULL) != 0)
	{
		return (1);
	}
	// monitor->die = die;
	// monitor->print = print;
	return (0);
}

int	init_threads(t_monitor *monitor)
{
	t_philo	*current;

	current = monitor->first;
	while (current)
	{
		if (pthread_create(&current->thread, NULL, (void*)test /*&routine*/,
				current) != 0)
		{
			printf("Failed to create thread for philo %d\n", current->id);
			return (1);
		}
		current = current->next;
	}
	current = monitor->first;
	while (current)
	{
		if (pthread_join(current->thread, NULL) != 0)
		{
			printf("Failed to join thread for philosopher %d\n", current->id);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	test(void)
{
	printf("test\n");
}