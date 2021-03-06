/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:35:37 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/21 14:50:06 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_args_check(t_info *info, char **argv, int argc)
{
	info->philo_num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (pthread_mutex_init(&info->mutex_count, NULL) != 0
		|| pthread_mutex_init(&info->mutex_print, NULL) != 0)
		return (0);
	if (argc == 6)
		info->time_to_win = ft_atoi(argv[5]);
	else
		info->time_to_win = 0;
	if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_sleep < 60)
		return (0);
	info->done_eating = 0;
	info->is_dead = 0;
	info->init_time = ft_get_time();
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

static int	add_values(int len, t_philo **philo, pthread_t **new, t_info *info)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (pthread_mutex_init(&(*philo)[i].fork, NULL) != 0)
			return (ft_free(*philo, *new, 2));
		(*philo)[i].id = i;
		(*philo)[i].last_meal = ft_get_time();
		if (i + 1 == len)
			(*philo)[i].right_philo = &(*philo)[0];
		else
			(*philo)[i].right_philo = &(*philo)[i + 1];
		(*philo)[i].infos = info;
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
	if (!add_values(len, philo, new_thread, info))
		return (0);
	return (1);
}
