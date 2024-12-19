/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:17:17 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/19 18:03:37 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_list_philo(t_monitor *monitor)
{
	t_philo	*current;

	printf("philo id = %d\n", monitor->first->id);
	if (monitor->first->next)
	{
		current = monitor->first->next;
		while (current) //gerer le cas ou il y a doublement chainee
		{
			printf("philo id = %d\n", current->id);
			current = current->next;
		}
	}
	printf("End of the list\n");
}

void	ft_free_all(t_monitor *monitor)
{
	t_philo	*current;
	t_philo	*next;

	if (monitor->first)
	{
		current = monitor->first;
		if (monitor->first->next)
		{
			while (current)
			{
				next = monitor->first->next;
				free(current);
				current = next;
			}
		}
		else
			free(current);
		free(monitor);
	}
}
