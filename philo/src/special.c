/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 14:22:48 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 14:45:51 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	one_philo(t_philo *philo)
{
	ft_printf(philo, FORK);
	ft_usleep(philo, philo->monitor->data->td);
	printf("%lu %d %s\n", get_current_time()
		- philo->monitor->data->starting_time, philo->id, DIED);
	return ;
}

pthread_mutex_t	*get_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->r_fork);
	return (philo->l_fork);
}

pthread_mutex_t	*get_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (philo->l_fork);
	return (philo->r_fork);
}

long	ft_atoi_spe(char *str)
{
	size_t		i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (2147483648);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (2147483648);
		if (handle_overflow(res, str[i]))
			return (2147483648);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
