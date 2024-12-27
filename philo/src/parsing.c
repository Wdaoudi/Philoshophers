/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:53:50 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 14:19:15 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parsing_argument(char **av, t_data *data)
{
	int	i;

	i = 0;
	i = 1;
	while (av[i])
	{
		if (is_right_argument(av[i]) == 1)
			return (1);
		i++;
	}
	data->av = av;
	fill_data(data);
	return (0);
}

void	fill_data(t_data *data)
{
	data->philo = ft_atoi_spe(data->av[1]);
	data->td = ft_atoi_spe(data->av[2]);
	data->te = ft_atoi_spe(data->av[3]);
	data->ts = ft_atoi_spe(data->av[4]);
	data->starting_time = get_current_time();
	if (data->av[5])
	{
		data->nftepme = ft_atoi_spe(data->av[5]);
		data->flag = true;
	}
	else
	{
		data->nftepme = -1;
		data->flag = false;
	}
}

int	is_right_argument(char *str)
{
	if (is_only_space(str) == 1 || ft_atoi_spe(str) == 2147483648)
		return (1);
	return (0);
}

int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	handle_overflow(long res, char digit)
{
	if (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && (digit - '0') > LONG_MAX
			% 10))
		return (1);
	return (0);
}
