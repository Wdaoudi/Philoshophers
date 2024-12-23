/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:02:09 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/23 19:11:06 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_state	ft_printf(t_philo *philo, char *message)
{
	size_t	time;

	// if (pthread_mutex_lock(philo->r_fork) != 0)
	// 	return (set_simulation_finish(philo));
	if (check_if_dead(philo) == FINISH)
	{
		pthread_mutex_unlock(&philo->monitor->print);
		return (FINISH);
	}
	time = get_current_time() - philo->monitor->data->starting_time;
	printf("%lu %d %s\n", time, philo->id, message);
	if (pthread_mutex_unlock(&philo->monitor->print) != 0)
		return (set_simulation_finish(philo));
	return (CONTINUE);
}
