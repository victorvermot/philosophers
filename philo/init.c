/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:35:37 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/22 21:57:02 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_args_check(t_time *time, char **argv)
{
	time->time_to_die = ft_atoi(argv[2]);
	time->time_to_eat = ft_atoi(argv[3]);
	time->time_to_sleep = ft_atoi(argv[4]);
	if (!time->time_to_die || !time->time_to_eat || !time->time_to_sleep)
		return (0);
	return (1);
}

void	ft_free(t_thread *thread, int opt)
{
	if (opt == 1)
	{
		free(thread->new_thread);
		free(thread->fork);
	}
	else if (opt == 2)
	{
		free(thread->new_thread);
		free(thread->fork);
		free(thread->philo);
	}
	else
	{
		free(thread->new_thread);
		free(thread->fork);
		free(thread->philo);
		free(thread->times);
	}
}

int	ft_allocate(t_thread *thread, int len, char **argv)
{
	thread->new_thread = malloc(sizeof(pthread_t) * len);
	if (!thread->new_thread)
		return (0);
	thread->fork = malloc(sizeof(pthread_mutex_t) * len);
	if (!thread->fork)
	{
		free(thread->new_thread);
		return (0);
	}
	thread->philo = malloc(sizeof(t_philo) * len);
	if (!thread->philo)
	{
		ft_free(thread, 1);
		return (0);
	}
	thread->times = malloc(sizeof(t_time));
	if (!thread->times)
	{
		ft_free(thread, 3);
		return (0);
	}
	if (!ft_args_check(thread->times, argv))
		return (0);
	return (1);
}
