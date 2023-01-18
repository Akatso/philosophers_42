/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:55:45 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:56:26 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_speak(t_philo *philo, char *s)
{
	if (ft_alright(philo))
	{
		pthread_mutex_lock(&philo->arg->m_print);
		printf("%lld ", ft_get_ts_ms() - philo->arg->begin);
		printf("%d %s\n", philo->id, s);
		pthread_mutex_unlock(&philo->arg->m_print);
	}
}

t_ts	ft_get_ts_ms(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	ft_set_mutex(pthread_mutex_t *mutex, long long *v, long long value)
{
	pthread_mutex_lock(mutex);
	*v = value;
	pthread_mutex_unlock(mutex);
}

long long	ft_get_mutex(pthread_mutex_t *mutex, long long *variable)
{
	long long	save;

	pthread_mutex_lock(mutex);
	save = *variable;
	pthread_mutex_unlock(mutex);
	return (save);
}

int	ft_stderr(char *error)
{
	size_t	i;

	i = 0;
	while (error[i])
		i++;
	return (write(2, error, i));
}
