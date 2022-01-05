/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:28:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/05 18:12:40 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	//pthread_mutex_lock(thread->fork);
	//usleep(thread->times->time_to_eat);
	//pthread_mutex_unlock(thread->fork);
	gettimeofday(&philo->c_time, NULL);
	while (philo->c_time.tv_usec - philo->last_meal > philo->infos->time_to_eat)
	{
		usleep(philo->infos->time_to_eat);
		ft_write_msg(philo, EAT);
		usleep(philo->infos->time_to_sleep);
		ft_write_msg(philo, SLEEP);
		// printf("%d\n", philo->c_time.tv_usec - philo->last_meal > philo->time.time_to_eat);
		// return ;
		gettimeofday(&philo->c_time, NULL);
	}
	philo->is_dead = 1;
	//ft_sleep(thread);
}

static void	*ft_test(void *arg)
{
	t_philo				*philo;
	//pthread_mutex_t		*fork;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(50);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->right_philo->fork);
	//ft_write_msg(philo, FORK);
	printf("%d\n", philo->infos->time_to_sleep);
	//ft_eat(philo);
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
	return (0);
}

int	ft_launch_thread(t_philo *philo, int len, pthread_t *new_thread)
{
	int	i;

	i = -1;
	printf("%d\n", philo->infos->time_to_win);
	while (++i < len)
	{
		//printf("%d", philo[i].right_philo->id);
		if (pthread_mutex_init(&philo[i].fork, NULL) != 0)
			return (ft_free(philo, new_thread, 2));
		if (pthread_create(&new_thread[i], NULL,
				ft_test, &philo[i]) != 0)
			return (ft_free(philo, new_thread, 2));
		pthread_mutex_destroy(&philo[i].fork);
	}
	i = 0;
	while (i < len)
	{
		if (pthread_join(new_thread[i++], NULL) != 0)
			return (ft_free(philo, new_thread, 2));
	}
	return (1);
}
