/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:01:46 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/23 15:16:39 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// Implémentation de la routine du philosophe
	while (!philo->monitor->is_die)
	{
		// Logique du philosophe (manger, dormir, penser)
	}
	return (NULL);
}