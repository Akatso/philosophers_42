/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:35 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:53:22 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo)
{
	ft_speak(philo, "is sleeping");
	usleep(1000 * philo->arg->tt_sleep);
}

void	ft_eat(t_philo *philo, int *eat)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_speak(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_speak(philo, "has taken a fork");
	(*eat)++;
	ft_speak(philo, "is eating");
	pthread_mutex_lock(&philo->arg->m_all_eat);
	if (philo->arg->nb_eat > 0 && *eat == philo->arg->nb_eat)
	{
		philo->arg->all_eat += 1;
		pthread_mutex_unlock(&philo->arg->m_all_eat);
		usleep(1000 * philo->arg->tt_eat);
		ft_set_mutex(&philo->m_last_eat, &philo->last_eat, ft_get_ts_ms());
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_unlock(&philo->arg->m_all_eat);
	usleep(1000 * philo->arg->tt_eat);
	ft_set_mutex(&philo->m_last_eat, &philo->last_eat, ft_get_ts_ms());
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_death(t_philo *philo, t_arg *arg)
{
	int		i;
	t_ts	current_last_eat;

	while (1)
	{
		i = 0;
		while (i < arg->nb_philo)
		{
			current_last_eat = ft_get_mutex(&philo[i].m_last_eat,
					&philo[i].last_eat);
			if (ft_get_ts_ms() - current_last_eat >= arg->tt_die)
			{
				ft_speak(&philo[i], "died");
				pthread_mutex_lock(&arg->m_died);
				arg->died = 1;
				pthread_mutex_unlock(&arg->m_died);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
