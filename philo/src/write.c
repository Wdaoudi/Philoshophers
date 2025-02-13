/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:02:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 14:45:30 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_state	ft_printf(t_philo *philo, char *message)
{
	size_t	time;

	if (get_simulation_state(philo) == FINISH)
		return (FINISH);
	if (pthread_mutex_lock(&philo->monitor->print) != 0)
		return (set_simulation_finish(philo));
	time = get_current_time() - philo->monitor->data->starting_time;
	printf("%lu %d %s\n", time, philo->id, message);
	if (pthread_mutex_unlock(&philo->monitor->print) != 0)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}

void	ft_printdead(t_philo *philo, char *message)
{
	size_t	time;

	time = get_current_time() - philo->monitor->data->starting_time;
	printf("%lu %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->monitor->print);
	return ;
}
