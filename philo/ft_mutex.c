/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:05 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:50:08 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_init_mutex(t_philo *philo, t_arg *arg)
{
	int	i;

	pthread_mutex_init(&arg->m_print, NULL);
	pthread_mutex_init(&arg->m_died, NULL);
	pthread_mutex_init(&arg->m_all_eat, NULL);
	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_mutex_init(&philo[i].m_last_eat, NULL);
		i++;
	}
	ft_init_forks(philo, arg);
}

void	ft_init_forks(t_philo *philo, t_arg *arg)
{
	int	i;

	i = 1;
	philo[0].arg = arg;
	philo[0].id = 1;
	pthread_mutex_init(&philo[0].l_fork, NULL);
	if (philo->arg->nb_philo == 1)
		return ;
	philo[0].state = EATING;
	philo[0].r_fork = &philo[arg->nb_philo - 1].l_fork;
	while (i < arg->nb_philo)
	{
		philo[i].arg = arg;
		philo[i].state = EATING;
		philo[i].id = i + 1;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		philo[i].r_fork = &philo[i - 1].l_fork;
		i++;
	}
}

void	ft_destroy_mutex(t_philo *philo)
{
	int		i;

	i = 0;
	if (philo->arg->nb_philo == 1)
	{
		pthread_mutex_destroy(&philo[0].l_fork);
		return ;
	}
	pthread_mutex_destroy(&philo->arg->m_print);
	pthread_mutex_destroy(&philo->arg->m_died);
	pthread_mutex_destroy(&philo->arg->m_all_eat);
	while (i < philo->arg->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].m_last_eat);
		pthread_mutex_destroy(&philo[i].l_fork);
		i++;
	}
}
