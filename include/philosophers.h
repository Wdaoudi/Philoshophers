/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:26:26 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/20 12:22:18 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

// typedef struct s_fork
// {
// 	pthread_mutex_t fork_lock; // quand un philo predns il lock
// 	bool				in_use;
// 	/* si la fourchette de droite n est pas dispo il unock
// 	sa fourchette pour eviter les deadlocks */
// }						t_fork;

typedef struct s_data
{
	char			**av;
	long			philo;
	long			td;
	long			te;
	long			ts;
	long			nftepme;
	bool			flag;
}					t_data;

typedef struct s_monitor
{
	struct s_philo	*first;
	pthread_mutex_t	die;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
	bool			is_die;
	t_data			*data;

}					t_monitor;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				id;
	int				number_of_meal;
	int				last_meal_time;
	size_t			starting_time;
	t_monitor		*monitor;
	struct s_philo	*next;
}					t_philo;

/* parsing */

int					parsing_argument(char **av, t_data *data);
int					handle_overflow(long res, char digit);
long				ft_atoi_spe(char *str);
int					ft_isdigit(int c);
void				fill_data(t_data *data);
int					is_right_argument(char *str);
int					is_only_space(char *str);

/* list creation*/

int					create_philo_list(t_monitor *monitor);
void				add_to_list(t_monitor *monitor, t_philo *new);
t_philo				*create_philo(t_monitor *monitor, int i);
int					init_monitor(t_data *data, t_monitor *monitor);
int					init_threads(t_monitor *monitor);

/* thread + mutex*/
int					assign_forks(t_monitor *monitor);

/* utils*/

void				ft_putstr_fd(char *s, int fd);
void				ft_free_all(t_monitor *monitor);
size_t				get_current_time(void);
/* test*/
void				print_list_philo(t_monitor *monitor);
void				test(void);

/*
strcture table: avec dedans un  mutex pour le printf et
un thread avec un superviseur en boleen qui dis si oui ou
on conitinue dans le cas ou un philo meurt on stop tout


structure d une liste chainee un maillon= un philo:

un philo peut mourrir en mangeant donc necessaire de
prednre en compte le temps de nourrissement


attention usleep en microsecond donc
usleep(time_to_sleep * 1000);

printf X has taken a fork // seulement si le philo a deux fourchette


usleep apres la creation d un thread pour lancer une routine
1 millisecond


time_to_think = (time_to_die - (get_time_in_ms() - philo->last_meal)
		- time_to_eat) / 2
necessaire pour laisser certains philo manger. mais pas superieur
a 500 / 600 ms


*/

#endif