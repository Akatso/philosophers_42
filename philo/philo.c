/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:30 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:49:36 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo(t_arg *arg)
{
	t_philo		philo[MAX];
	pthread_t	thread_id[MAX];
	int			i;

	i = 0;
	ft_init_mutex(philo, arg);
	arg->begin = ft_get_ts_ms();
	while (i < arg->nb_philo)
	{
		philo[i].last_eat = arg->begin;
		pthread_create(&thread_id[i], NULL, &ft_routine, &philo[i]);
		i++;
	}
	ft_death(philo, arg);
	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_join(thread_id[i], NULL);
		i++;
	}
	ft_destroy_mutex(philo);
	return ;
}

int	main(int ac, char **av)
{
	t_arg	arg;

	if (ft_error(&arg, av, ac) == -1)
		return (-1);
	if (arg.nb_philo > 1)
		ft_philo(&arg);
	else
		ft_alone(&arg);
	return (0);
}
