/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:43 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:59:04 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX		250

# define EATING		1
# define SLEEPING	2
# define THINKING	3

typedef long long	t_ts;

typedef struct s_arg
{
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_eat;
	int				all_eat;
	int				died;
	pthread_mutex_t	m_died;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_all_eat;
	t_ts			begin;
}	t_arg;

typedef struct s_philo
{
	int				id;
	int				state;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	m_last_eat;
	t_ts			last_eat;
	t_arg			*arg;
}	t_philo;

// PARSE
int			ft_atoi(char *av);
int			ft_check(char **av);
void		ft_init_struct(t_arg *arg);
int			ft_parse(t_arg *arg, char **av, int ac);
int			ft_error(t_arg *arg, char **av, int ac);

// UTILS
void		ft_speak(t_philo *philo, char *s);
void		ft_set_mutex(pthread_mutex_t *mutex, long long *v, long long value);
long long	ft_get_mutex(pthread_mutex_t *mutex, long long *variable);
t_ts		ft_get_ts_ms(void);
int			ft_stderr(char *error);

// MUTEX
void		ft_init_mutex(t_philo *philo, t_arg *arg);
void		ft_init_forks(t_philo *philo, t_arg *arg);
void		ft_destroy_mutex(t_philo *philo);

// STATE
void		ft_sleep(t_philo *philo);
void		ft_eat(t_philo *philo, int *eat);
void		ft_death(t_philo *philo, t_arg *arg);

// ROUTINE
void		ft_change_state(t_philo *philo);
int			ft_alright(t_philo *philo);
void		*ft_routine(void *philo_void);

// ALONE
void		*ft_only(void *philo_void);
int			ft_alone(t_arg *arg);

// MAIN
void		ft_philo(t_arg *arg);

#endif
