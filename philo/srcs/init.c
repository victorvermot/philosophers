/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:35:37 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/07 12:30:13 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_args_check(t_info *info, char **argv, int opt)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (opt == 1)
		info->time_to_win = ft_atoi(argv[5]);
	else
		info->time_to_win = 0;
	if (!info->time_to_die || !info->time_to_eat || !info->time_to_sleep
		|| !info->time_to_win)
		return (0);
	info->is_printed = 0;
	return (1);
}

int	ft_free(t_philo *philo, pthread_t *new_thread, int opt)
{
	if (opt == 1)
		free(philo);
	else
	{
		free(philo);
		free(new_thread);
	}
	return (0);
}

static int	add_values(int len, t_philo **philo, t_info *info)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		(*philo)[i].id = i;
		gettimeofday(&(*philo)[i].c_time, NULL);
		(*philo)[i].last_meal = (*philo)[i].c_time.tv_usec;
		if (!(i + 1 == len))
			(*philo)[i].right_philo = &(*philo)[i + 1];
		else
			(*philo)[i].right_philo = &(*philo)[0];
		(*philo)[i].infos = info;
		(*philo)[i].is_dead = 0;
		(*philo)[i].head = &(*philo)[0];
		(*philo)[i].meal_count = 0;
		(*philo)[i].done_eating = 0;
	}
	return (1);
}

int	ft_allocate(t_philo **philo, pthread_t **new_thread, t_info *info, int len)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * len);
	if (!*philo)
		return (0);
	*new_thread = (pthread_t *)malloc(sizeof(pthread_t) * len);
	if (!*new_thread)
	{
		free(*philo);
		return (0);
	}
	add_values(len, philo, info);
	//printf("Last meal vaut%d\n", (*philo)->last_meal);
	return (1);
}
