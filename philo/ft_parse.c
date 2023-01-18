/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slepetit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 12:05:15 by slepetit          #+#    #+#             */
/*   Updated: 2023/01/17 19:50:35 by slepetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *av)
{
	long int	nb;
	long int	i;

	nb = 0;
	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (-1);
		nb = (nb * 10) + av[i] - 48;
		if (nb < 1 || nb > INT_MAX)
			return (-1);
		i++;
	}
	return (nb);
}

int	ft_check(char **av)
{
	long int	nb;
	long int	i;
	long int	j;

	nb = 0;
	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
			nb = (nb * 10) + av[i][j] - 48;
			if (nb < 0 || nb > INT_MAX)
				return (-1);
			j++;
		}
		if (nb == 0)
			return (-1);
		nb = 0;
		j = 0;
		i++;
	}
	return (0);
}

void	ft_init_struct(t_arg *arg)
{
	arg->nb_philo = 0;
	arg->tt_die = 0;
	arg->tt_eat = 0;
	arg->tt_sleep = 0;
	arg->nb_eat = 0;
	arg->died = 0;
	arg->all_eat = 0;
}

int	ft_parse(t_arg *arg, char **av, int ac)
{
	ft_init_struct(arg);
	if (ft_check(av) == -1)
		return (-1);
	arg->nb_philo = ft_atoi(av[1]);
	if (arg->nb_philo > MAX)
		return (-1);
	arg->tt_die = ft_atoi(av[2]);
	arg->tt_eat = ft_atoi(av[3]);
	arg->tt_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->nb_eat = ft_atoi(av[5]);
	return (0);
}

int	ft_error(t_arg *arg, char **av, int ac)
{
	if (ac < 5 || ac > 6)
	{
		ft_stderr("Error.\nThe number of arguments must be 5 or 6.\n");
		return (-1);
	}
	if (ft_parse(arg, av, ac) == -1)
	{
		ft_stderr("Error.\nArguments must be positive integers only.\n");
		ft_stderr("The number of philo must be less than or equal to 250.\n");
		return (-1);
	}
	return (0);
}
