/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 15:46:29 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1);
	if (philo->monitor->data->philo == 1)
		return (one_philo(philo), NULL);
	while (1)
	{
		if (eat(philo) == FINISH)
			break ;
		if (philo->number_of_meal == philo->monitor->data->nftepme)
		{
			break ;
		}
		if (ft_sleep(philo) == FINISH)
			break ;
		if (think(philo) == FINISH)
			break ;
	}
	return (NULL);
}

t_state	eat(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (take_fork(philo) == FINISH)
		return (FINISH);
	if (ft_printf(philo, EATING) == FINISH)
		return (drop_forks(philo), FINISH);
	philo->last_meal_time = get_current_time();
	if (ft_usleep(philo, philo->monitor->data->te) == FINISH)
		return (drop_forks(philo), FINISH);
	philo->number_of_meal += 1;
	drop_forks(philo);
	return (check_if_dead(philo));
}

t_state	think(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (ft_printf(philo, THINKING) == FINISH)
		return (FINISH);
	if (philo->monitor->data->philo % 2 == 0)
		ft_usleep(philo, philo->monitor->data->te - philo->monitor->data->ts);
	else
		ft_usleep(philo, (2 * philo->monitor->data->te)
			- philo->monitor->data->ts);
	return (CONTINUE);
}

t_state	ft_sleep(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (ft_printf(philo, SLEEPING) == FINISH)
		return (FINISH);
	if (ft_usleep(philo, philo->monitor->data->ts) == FINISH)
		return (FINISH);
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	return (CONTINUE);
}

t_state	check_if_dead(t_philo *philo)
{
	long	actual_time;
	long	last_meal;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	actual_time = get_current_time();
	last_meal = philo->last_meal_time;
	if ((actual_time - philo->last_meal_time) >= philo->monitor->data->td)
	{
		pthread_mutex_lock(&philo->monitor->die);
		if (philo->monitor->is_die != FINISH)
		{
			pthread_mutex_lock(&philo->monitor->print);
			printf("%lu %d %s\n", get_current_time()
				- philo->monitor->data->starting_time, philo->id, DIED);
			pthread_mutex_unlock(&philo->monitor->print);
			philo->monitor->is_die = FINISH;
		}
		pthread_mutex_unlock(&philo->monitor->die);
		return (FINISH);
	}
	return (CONTINUE);
}
