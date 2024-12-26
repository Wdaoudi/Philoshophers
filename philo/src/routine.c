/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/26 12:48:02 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1); // milliseconde
	if (philo->monitor->data->philo == 1)
		return (one_philo(philo), NULL);
	while (1)
	{
		if (eat(philo) == FINISH)
			break ;
		if (philo->number_of_meal == philo->monitor->data->nftepme)
		{
			// printf("philo[%d] ate %d meal\n", philo->id, philo->number_of_meal);
			break ;
		}
		if (ft_sleep(philo) == FINISH)
			break ;
		if (think(philo) == FINISH)
			break ;
	}
	return (NULL);
}

t_state	take_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	// if (philo->id % 2 == 0 || philo->monitor->data->philo % 2 != 0)
	// {
	// 	first_fork = philo->r_fork;
	// 	second_fork = philo->l_fork;
	// }
	// else
	// {
	// 	first_fork = philo->l_fork;
	// 	second_fork = philo->r_fork;
	// }
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
		// pthread_mutex_unlock(second_fork);
		// pthread_mutex_unlock(first_fork);
		drop_forks(philo);
		return (FINISH);
	}
	// if (ft_printf(philo, FORK) == FINISH)
	// {
	// 	pthread_mutex_unlock(second_fork);
	// 	pthread_mutex_unlock(first_fork);
	// 	drop_forks(philo);
	// 	return (FINISH);
	// }
	return (CONTINUE);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0 || philo->monitor->data->philo % 2 == 0)
	{ // philo.monitor.data.philo %2 != 0
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

t_state	eat(t_philo *philo)
{
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (take_fork(philo) == FINISH)
		return (FINISH);
	if (ft_printf(philo, EATING) == FINISH)
		return (drop_forks(philo), FINISH);
	philo->last_meal_time = get_current_time(); // en milliseconde
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
		return (FINISH); // * 1000 passage en useconde
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
	long	time;

	pthread_mutex_lock(&philo->monitor->die);
	if (philo->monitor->is_die != FINISH)
	{
		pthread_mutex_lock(&philo->monitor->print);
		time = get_current_time() - philo->monitor->data->starting_time;
		printf("%lu %d %s\n", time, philo->id, DIED);
		pthread_mutex_unlock(&philo->monitor->print);
	}
	philo->monitor->is_die = FINISH;
	pthread_mutex_unlock(&philo->monitor->die);
	return (FINISH);
}

// t_state	check_if_dead(t_philo *philo)
// {
// 	long	actual_time;
// 	long	last_meal;
// 	t_state state;

// 	if (get_simulation_state(philo) == FINISH)
// 		return (FINISH);

// 	if (pthread_mutex_lock(&philo->monitor->meal_check) != 0)
// 		return (set_simulation_finish(philo));
// 	actual_time = get_current_time(); // en milliseconde
// 	last_meal = philo->last_meal_time;
// 	if ((actual_time - philo->last_meal_time) >= philo->monitor->data->td)
// 		return (pthread_mutex_unlock(&philo->monitor->meal_check),
// 			set_simulation_finish(philo));
// 	if (pthread_mutex_unlock(&philo->monitor->meal_check) != 0)
// 		return (set_simulation_finish(philo));
// 	return (CONTINUE);
// }

t_state	check_if_dead(t_philo *philo)
{
	long	actual_time;
	long	last_meal;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	actual_time = get_current_time(); // en milliseconde
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
