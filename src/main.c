/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:52:24 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/19 14:31:53 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int ac, char **av)
{
	int	i;
    t_data data;
    // pthread_mutex_t mutex;
	i = 0;
    (void)i;
	if (ac != 6 && ac != 5)
		return (printf("Invalid number of argument\n"), 1);
	if (parsing_argument(av,&data) != 0)
		return (printf("Invalid argument\n"),1);
    // printf ("philo= %ld\ntd= %ld\nte= %ld\n ts= %ld\nnftepme= %ld\n 6th argument %d\n", data.philo, data.td, data.te, data.ts, data.nftepme, data.flag);
    // init_struct();

	// if(pthread_create(th[i],) && pthread_mutex_init())
    // {
        
    // }
    // if(pthread_join())
    // {
        
    // }
    // pthread_mutex_destroy();
    return (0);
}

/*
timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.

gettimeofday(struct timeval *tv, NULL);
return 0 si success or -1 if failed;

*/