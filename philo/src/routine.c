/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/25 15:24:12 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->monitor->data->flag == true
			/*&& philo->number_of_meal == philo->monitor->data->nftepme*/)
		{
			if (check_if_all_ate_enough(philo/*->monitor*/) == FINISH)
			{
				printf("philo[%d] ate enough ate %d\n", philo->id,
					philo->number_of_meal);
				break ;
			}
		}
		if (eat(philo) == FINISH)
		{
			// printf("philo[%d] is dead at %lu\n", philo->id, get_current_time()
			// 	- philo->starting_time);
			break ;
		}
		if (philo->monitor->data->flag == true
			/*&& philo->number_of_meal == philo->monitor->data->nftepme*/)
		{
			if (check_if_all_ate_enough(philo /*->monitor*/) == FINISH)
			{
				printf("philo[%d] ate enough ate %d\n", philo->id,
					philo->number_of_meal);
				break ;
			}
		}
		if (ft_sleep(philo) == FINISH)
		{
			// printf("philo[%d] is dead at %lu\n", philo->id, get_current_time()
			// 	- philo->starting_time);
			break ;
		}
		if (think(philo) == FINISH)
		{
			// printf("philo[%d] is dead at %lu\n", philo->id, get_current_time()
			// 	- philo->starting_time);
			break ;
		}
	}
	return (NULL);
}

// t_state	take_fork(t_philo *philo)
// {
// 	if (check_if_dead(philo) == FINISH)
// 		return (FINISH);
// 	if (pthread_mutex_lock(philo->r_fork) != 0)
// 		return (set_simulation_finish(philo));
// 	if (check_if_dead(philo) == FINISH)
// 		return (pthread_mutex_unlock(philo->r_fork), FINISH);
// 	if (ft_printf(philo, FORK) == FINISH)
// 		return (pthread_mutex_unlock(philo->r_fork), FINISH);
// 	if (philo->monitor->data->philo == 1)
// 	{
// 		usleep(philo->monitor->data->td * 1000);
// 		return (pthread_mutex_unlock(philo->r_fork), FINISH);
// 	}
// 	if (pthread_mutex_lock(philo->l_fork) != 0)
// 		return (pthread_mutex_unlock(philo->r_fork),
// 			set_simulation_finish(philo));
// 	if (check_if_dead(philo) == FINISH)
// 	{
// 		pthread_mutex_unlock(philo->r_fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 		return (FINISH);
// 	}
// 	if (ft_printf(philo, FORK) == FINISH)
// 	{
// 		pthread_mutex_unlock(philo->r_fork);
// 		pthread_mutex_unlock(philo->l_fork);
// 		return (FINISH);
// 	}
// 	return (CONTINUE);
// }
// tentative de ralentissement de la prise des fourchettes en focntiond e la position

t_state	take_fork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	else
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
		usleep(100); // ralentir la prise de decision
	}
	if (check_if_dead(philo) == FINISH)
		return (FINISH);
	if (pthread_mutex_lock(first_fork) != 0)
		return (set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
		return (pthread_mutex_unlock(first_fork), FINISH);
	if (ft_printf(philo, FORK) == FINISH)
		return (pthread_mutex_unlock(first_fork), FINISH);
	if (philo->monitor->data->philo == 1)
	{
		usleep(philo->monitor->data->td * 1000);
		return (pthread_mutex_unlock(first_fork), FINISH);
	}
	if (pthread_mutex_lock(second_fork) != 0)
		return (pthread_mutex_unlock(first_fork), set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
		return (FINISH);
	}
	if (ft_printf(philo, FORK) == FINISH)
	{
		pthread_mutex_unlock(first_fork);
		pthread_mutex_unlock(second_fork);
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
	usleep(philo->monitor->data->te * 1000);
	// passsage en useconde arguments de usleep
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
	if (philo->monitor->is_die != FINISH)
		ft_printdead(philo, DIED);
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
	if ((actual_time - philo->last_meal_time) >= philo->monitor->data->td)
		return (pthread_mutex_unlock(&philo->monitor->meal_check),
			set_simulation_finish(philo));
	if (pthread_mutex_unlock(&philo->monitor->meal_check) != 0)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}

// t_state	check_if_all_ate_enough(t_monitor *monitor)
// {
// 	t_philo *current;
// 	pthread_mutex_lock(&monitor->meal_check);
// 	current = monitor->first;
// 	while (current)
// 	{
// 		if (current->number_of_meal < monitor->data->nftepme)
// 		{
// 			pthread_mutex_unlock(&monitor->meal_check);
// 			return (CONTINUE);
// 		}
// 		current = current->next;
// 	}
// 	pthread_mutex_unlock(&monitor->meal_check);
// 	return (FINISH);
// }

t_state	check_if_all_ate_enough(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->meal_check);
	if (philo->number_of_meal < philo->monitor->data->nftepme)
	{
		pthread_mutex_unlock(&philo->monitor->meal_check);
		return (CONTINUE);
	}
	pthread_mutex_unlock(&philo->monitor->meal_check);
	return (FINISH);
}
