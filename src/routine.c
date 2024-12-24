/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/24 15:04:24 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (eat(philo) == FINISH)
			break ;
		if (philo->monitor->data->flag == true
			&& philo->number_of_meal == philo->monitor->data->nftepme)
		{
			printf("dead or finish eating\n");
			break ;
		}
		if (ft_sleep(philo) == FINISH)
			break ;
		think(philo);
		// printf("boucle dans la routine\n");
		// think
		// if (philo->monitor->data->philo % 2 == 0)
		// {
		// }
		// else
		// {
		// 	return (0);
		// }
		//! philo->monitor->is_die
		// Logique du philosophe (manger, dormir, penser)
	}
	return (NULL);
}

t_state	take_fork(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
		return (pthread_mutex_unlock(philo->r_fork), FINISH);
	if (ft_printf(philo, FORK) == FINISH)
		return (pthread_mutex_unlock(philo->r_fork), FINISH);
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (pthread_mutex_unlock(philo->r_fork),
			set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (FINISH);
	}
	if (ft_printf(philo, FORK) == FINISH)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (FINISH);
	}
	return (CONTINUE);
}

t_state	eat(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (take_fork(philo) == FINISH)
		return (FINISH);
	ft_printf(philo, EATING);
	philo->last_meal_time = get_current_time();
	usleep(philo->monitor->data->te);
	philo->number_of_meal += 1;
	if (check_if_dead(philo) == FINISH)
		return (pthread_mutex_unlock(philo->r_fork),
			pthread_mutex_unlock(philo->l_fork), FINISH);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (CONTINUE);
}

t_state	think(t_philo *philo)
{
	if (ft_printf(philo, THINKING) == FINISH)
		return (FINISH);
	return (CONTINUE);
}

t_state	ft_sleep(t_philo *philo)
{
	// long	timestamp;
	// if (check_if_dead(philo) == FINISH)
	// 	return (FINISH);
	// if (pthread_mutex_lock(&philo->monitor->print) == FINISH)
	// 	return (FINISH);
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	// timestamp = get_current_time();
	// timestamp = timestamp - philo->starting_time;
	if (ft_printf(philo, SLEEPING) == FINISH)
		return (FINISH);
	usleep(philo->monitor->data->ts);
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	return (CONTINUE);
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
	pthread_mutex_lock(&philo->monitor->die);
	philo->monitor->is_die = FINISH;
	pthread_mutex_unlock(&philo->monitor->die);
	return (FINISH);
}

t_state	check_if_dead(t_philo *philo)
{
	long actual_time;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	actual_time = get_current_time();
	printf("actual time by phil[%d] and time is %lu\n", philo->id, (actual_time
			- philo->starting_time) / 1000);
	if ((actual_time - philo->last_meal_time) >= philo->monitor->data->td)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}