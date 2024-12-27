/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdaoudi- <wdaoudi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:26:26 by wdaoudi-          #+#    #+#             */
/*   Updated: 2024/12/27 18:54:29 by wdaoudi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "is died"

typedef enum s_state
{
	CONTINUE,
	FINISH,
}					t_state;

typedef struct s_data
{
	char			**av;
	long			philo;
	long			td;
	long			te;
	long			ts;
	long			nftepme;
	bool			flag;
	long			starting_time;
}					t_data;

typedef struct s_monitor
{
	struct s_philo	*first;
	pthread_mutex_t	die;
	t_state			is_die;
	pthread_mutex_t	print;
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
	long long		last_meal_time;
	long			starting_time;
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
t_state				set_simulation_finish(t_philo *philo);

/* routine */

void				*routine(void *arg);
t_state				eat(t_philo *philo);
t_state				take_fork(t_philo *philo);
t_state				think(t_philo *philo);
t_state				ft_sleep(t_philo *philo);
t_state				ft_usleep(t_philo *philo, long time);

/* utils*/

void				ft_putstr_fd(char *s, int fd);
void				ft_free_all(t_monitor *monitor);
size_t				get_current_time(void);
t_state				set_simulation_finish(t_philo *philo);
t_state				get_simulation_state(t_philo *philo);
t_state				check_if_dead(t_philo *philo);
t_state				ft_printf(t_philo *philo, char *message);
void				ft_printdead(t_philo *philo, char *message);
void				ft_free_all(t_monitor *monitor);
int					fail_pthread_create(t_monitor *monitor, t_philo *current);

/* test*/

void				print_list_philo(t_monitor *monitor);

/* special*/
void				one_philo(t_philo *philo);
pthread_mutex_t		*get_first_fork(t_philo *philo);
pthread_mutex_t		*get_second_fork(t_philo *philo);
void				drop_forks(t_philo *philo);

#endif