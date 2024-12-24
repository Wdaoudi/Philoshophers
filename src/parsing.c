/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:53:50 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/24 15:30:36 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parsing_argument(char **av, t_data *data)
{
	int	i;
	// int	res;

	i = 0;
	// res = 0;
	// while (av[i++])
	// 	printf("av[%d] = %s\n", i, av[i]);
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
	data->td = ft_atoi_spe(data->av[2]); //en milliseconde
	data->te = ft_atoi_spe(data->av[3]);//en milliseconde
	data->ts = ft_atoi_spe(data->av[4]);//en milliseconde
	data->starting_time = get_current_time();//en milliseconde
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