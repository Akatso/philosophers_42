/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:51:10 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:52:13 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_change_state(t_philo *philo)
{
	if (philo->state == EATING)
		philo->state = SLEEPING;
	else if (philo->state == SLEEPING)
		philo->state = THINKING;
	else if (philo->state == THINKING)
		philo->state = EATING;
}

int	ft_alright(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->m_died);
	if (philo->arg->died == 1)
	{
		pthread_mutex_unlock(&philo->arg->m_died);
		return (0);
	}
	pthread_mutex_unlock(&philo->arg->m_died);
	if (ft_get_mutex(&philo->arg->m_all_eat,
			(long long *)&philo->arg->all_eat) == philo->arg->nb_philo)
		return (0);
	return (1);
}

void	*ft_routine(void *philo_void)
{
	t_philo		*philo;
	int			eat;

	philo = philo_void;
	eat = 0;
	if (philo->id % 2)
		usleep(500);
	while (ft_alright(philo))
	{
		if (philo->state == EATING)
			ft_eat(philo, &eat);
		else if (philo->state == SLEEPING)
			ft_sleep(philo);
		else if (philo->state == THINKING)
			ft_speak(philo, "is thinking");
		ft_change_state(philo);
	}
	return (philo_void);
}
