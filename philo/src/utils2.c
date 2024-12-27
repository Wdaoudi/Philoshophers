/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:20:29 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 18:54:05 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_threads(t_monitor *monitor)
{
	t_philo	*current;

	current = monitor->first;
	while (current)
	{
		if (pthread_create(&current->thread, NULL, &routine,
				(void *)current) != 0)
		{
			if (fail_pthread_create(monitor, current) == 1)
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

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

t_state	get_simulation_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->monitor->die);
	state = philo->monitor->is_die;
	pthread_mutex_unlock(&philo->monitor->die);
	return (state);
}

t_state	set_simulation_finish(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->monitor->die);
	if (philo->monitor->is_die != FINISH)
	{
		pthread_mutex_lock(&philo->monitor->print);
		time = get_current_time() - philo->monitor->data->starting_time;
		printf("%lums %d %s\n", time, philo->id, DIED);
		pthread_mutex_unlock(&philo->monitor->print);
	}
	philo->monitor->is_die = FINISH;
	pthread_mutex_unlock(&philo->monitor->die);
	return (FINISH);
}

t_state	take_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (pthread_mutex_lock(first_fork) != 0)
		return (set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
		return (pthread_mutex_unlock(first_fork), FINISH);
	if (ft_printf(philo, FORK) == FINISH)
		return (pthread_mutex_unlock(first_fork), FINISH);
	if (pthread_mutex_lock(second_fork) != 0)
		return (pthread_mutex_unlock(first_fork), set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH || ft_printf(philo, FORK) == FINISH)
	{
		drop_forks(philo);
		return (FINISH);
	}
	return (CONTINUE);
}

int	fail_pthread_create(t_monitor *monitor, t_philo *current)
{
	t_philo *error;

	printf("Failed to create thread for philo %d\n", current->id);
	pthread_mutex_lock(&monitor->die);
	monitor->is_die = FINISH;
	pthread_mutex_unlock(&monitor->die);
	error = monitor->first;
	while (error != current)
	{
		if (pthread_join(error->thread, NULL) != 0)
		{
			printf("Failed to join thread for philosopher %d\n", current->id);
			return (1);
		}
		error = error->next;
	}
	return (1);
}