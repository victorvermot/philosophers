/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:28:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/07 12:48:03 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_check_death(t_philo *philo)
{
	int	i;
	int	count;
	pthread_mutex_t	mutex_count;

	count = 0;
	i = -1;
	if (pthread_mutex_init(&mutex_count, NULL) != 0
		|| philo->infos->is_printed)
		return (0);
	pthread_mutex_lock(&mutex_count);
	while (++i < philo->infos->philo_num)
	{
		if (philo[i].is_dead)
		{
			ft_write_msg(philo, DEATH);
			return (0);
		}
		if (philo[i].done_eating)
			count++;
	}
	if (count == philo->infos->philo_num && !philo->infos->is_printed)
	{
		printf("Philosophers are done eating\n");
		philo->infos->is_printed = 1;
		return (0);
	}
	pthread_mutex_unlock(&mutex_count);
	pthread_mutex_destroy(&mutex_count);
	return (1);
}

static int	ft_are_philo_hungry(t_philo *philo)
{
	// pthread_mutex_t	mutex_count;
	//printf("%d, and %d\n", philo->infos->time_to_win);
	// if (pthread_mutex_init(&mutex_count, NULL) != 0)
	// 	return (0);
	// pthread_mutex_lock(&mutex_count);
	//printf("nombres de meal : %d\n", philo->meal_count);
	if (philo->infos->time_to_win)
	{
		if (philo->meal_count == philo->infos->time_to_win)
		{
			philo->done_eating = 1;
		}
	}
	return (1);
}

void	ft_eat(t_philo *philo)
{
	gettimeofday(&philo->c_time, NULL);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->right_philo->fork);
	ft_write_msg(philo, FORK);
	if (philo->c_time.tv_usec - philo->last_meal < philo->infos->time_to_die)
	{
		usleep(philo->infos->time_to_eat);
		ft_write_msg(philo, EAT);
		if (philo->infos->time_to_win)
			ft_are_philo_hungry(philo);
		gettimeofday(&philo->c_time, NULL);
		philo->last_meal = philo->c_time.tv_usec;
	}
	else
		philo->is_dead = 1;
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
	// if (philo->infos->is_printed)
	// 	return ;
	ft_write_msg(philo, SLEEP);
	usleep(philo->infos->time_to_sleep);
	ft_write_msg(philo, THINK);
	//printf("where we at%d\n", philo->c_time.tv_usec - philo->last_meal);
	//if (philo->c_time.tv_usec - philo->last_meal < philo->infos->time_to_die)
}

static void	*ft_test(void *arg)
{
	t_philo				*philo;
	int					i;

	i = 0;
	philo = arg;
	if (philo->id % 2 == 0)
		usleep(90);
	//printf("%d\n", philo->infos->time_to_sleep);
	gettimeofday(&philo->c_time, NULL);
	philo->last_meal = philo->c_time.tv_usec;
	while (ft_check_death(philo->head))
		ft_eat(philo);
	return (0);
}

int	ft_launch_thread(t_philo *philo, int len, pthread_t *new_thread)
{
	int	i;

	i = -1;
	//printf("%d\n", philo->infos->time_to_win);
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
