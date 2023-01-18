/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:11:51 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/14 16:12:03 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_only(void *void_philo)
{
	t_philo	*philo;

	philo = void_philo;
	pthread_mutex_lock(&philo[0].l_fork);
	ft_speak(philo, "has taken a l_fork.");
	pthread_mutex_unlock(&philo[0].l_fork);
	return (NULL);
}

int	ft_alone(t_arg *arg)
{
	t_philo		philo[MAX];
	pthread_t	thread_id[MAX];

	ft_init_mutex(philo, arg);
	arg->begin = ft_get_ts_ms();
	philo[0].last_eat = arg->begin;
	pthread_create(&thread_id[0], NULL, ft_only, &philo[0]);
	ft_death(philo, philo->arg);
	pthread_join(thread_id[0], NULL);
	ft_destroy_mutex(philo);
	return (0);
}
