/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:14:01 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/21 14:57:15 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_clean(t_philo *philo, pthread_t *new_thread)
{
	int	i;

	i = -1;
	while (++i < philo->infos->philo_num)
		pthread_mutex_destroy(&philo[i].fork);
	pthread_mutex_destroy(&philo->infos->mutex_count);
	pthread_mutex_destroy(&philo->infos->mutex_print);
	ft_free(philo, new_thread, 2);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		*new_thread;
	t_info			info;
	int				len;

	philo = NULL;
	if (argc != 5 && argc != 6)
		return (0);
	if (!ft_args_check(&info, argv, argc))
		return (0);
	len = ft_atoi(argv[1]);
	if (len <= 0)
		return (0);
	if (!ft_allocate(&philo, &new_thread, &info, len))
		return (0);
	if (!ft_launch_thread(philo, len, new_thread))
		return (ft_clean(philo, new_thread));
	hold_door(philo);
	ft_clean(philo, new_thread);
	return (0);
}
