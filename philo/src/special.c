/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:22:48 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/26 13:31:00 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	one_philo(t_philo *philo)
{
	ft_printf(philo, FORK);
	ft_usleep(philo, philo->monitor->data->td);
	return ;
}

pthread_mutex_t	*get_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0) /* || philo->monitor->data->philo % 2 == 0*/
		return (philo->r_fork);
	return (philo->l_fork);
}

pthread_mutex_t	*get_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 )/* || philo->monitor->data->philo % 2 == 0*/
		return (philo->l_fork);
	return (philo->r_fork);
}