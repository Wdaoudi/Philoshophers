/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/24 16:32:31 by wdaoudi-         ###   ########.fr       */
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
		{
			printf("someones dead\n");
			break ;
		}
		if (philo->monitor->data->flag == true
			/*&& philo->number_of_meal == philo->monitor->data->nftepme*/)
		{
			if (check_if_all_ate_enough(philo->monitor) == FINISH)
			{
				printf("philo[%d] ate enough\n", philo->id);
				break ;
			}
		}
		if (ft_sleep(philo) == FINISH)
		{
			printf("someones dead\n");
			break ;
		}
		if (think(philo) == FINISH)
		{
			printf("someones dead\n");
			break ;
		} // printf("boucle dans la routine\n");
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
	philo->last_meal_time = get_current_time(); // en milliseconde
	usleep(philo->monitor->data->te * 1000);    // passsage en useconde
	pthread_mutex_lock(&philo->monitor->meal_check);
	philo->number_of_meal += 1;
	pthread_mutex_unlock(&philo->monitor->meal_check);
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
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (ft_printf(philo, SLEEPING) == FINISH)
		return (FINISH);
	usleep(philo->monitor->data->ts * 1000); // * 1000 passage en useconde
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
	long	actual_time;
	long	last_meal;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	if (pthread_mutex_lock(&philo->monitor->meal_check) != 0)
		return (set_simulation_finish(philo));
	actual_time = get_current_time(); // en milliseconde
	last_meal = philo->last_meal_time;
	if (pthread_mutex_unlock(&philo->monitor->meal_check) != 0)
		return (set_simulation_finish(philo));
	if ((actual_time - philo->last_meal_time) >= philo->monitor->data->td)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}

t_state	check_if_all_ate_enough(t_monitor *monitor)
{
	t_philo *current;
	pthread_mutex_lock(&monitor->meal_check);
	current = monitor->first;
	while (current)
	{
		if (current->number_of_meal < monitor->data->nftepme)
		{
			pthread_mutex_unlock(&monitor->meal_check);
			return (CONTINUE);
		}
		current = current->next;
	}
	pthread_mutex_unlock(&monitor->meal_check);
	return (FINISH);
}