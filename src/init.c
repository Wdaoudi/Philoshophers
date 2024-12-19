/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:02:58 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/19 18:01:04 by wdaoudi-         ###   ########.fr       */
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
		monitor->first = new;
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
	t_philo *new;
	// pthread_mutex_t fork;
	(void)monitor;
    
	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = i + 1;
	new->next = NULL;
	new->number_of_meal = 0;

	// new->fork = pthread_mutex_create();
	return (new);
}