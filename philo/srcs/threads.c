/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:28:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/07 15:30:27 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* static int	ft_check_death(t_philo *philo)
{
	int	i;
	int	count;
	pthread_mutex_t	mutex_count;

	count = 0;
	i = -1;
	if (pthread_mutex_init(&mutex_count, NULL) != 0)
		return (0);
	while (++i < philo->infos->philo_num)
	{
		if (philo->infos->is_dead && !philo->infos->is_printed)
		{
			ft_write_msg(philo, DEATH);
			philo->infos->is_printed = 1;
			return (0);
		}
		if (philo[i].done_eating)
			count++;
	}
	pthread_mutex_lock(&mutex_count);
	if (count == philo->infos->philo_num && !philo->infos->is_printed)
	{
		printf("le printed : %d\n", philo->infos->is_printed);
		if (!philo->infos->is_printed)
			printf("Philosophers are done eating\n");
		philo->infos->is_printed = 1;
		return (0);
	}
	pthread_mutex_unlock(&mutex_count);
	pthread_mutex_destroy(&mutex_count);
	return (1);
} */

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
	pthread_mutex_lock(&philo->fork);
	ft_write_msg(philo, FORK);
	pthread_mutex_lock(&philo->right_philo->fork);
	ft_write_msg(philo, FORK);
	printf("le last meal %ld\n", ft_get_time() - philo->last_meal);
	if (ft_get_time() - philo->last_meal <= (size_t)philo->infos->time_to_die)
	{
		ft_write_msg(philo, EAT);
		usleep(philo->infos->time_to_eat);
		philo->meal_count += 1;
		if (philo->infos->time_to_win)
			ft_are_philo_hungry(philo);
		philo->last_meal = ft_get_time();
	}
	else
	{
		philo->infos->is_dead = 1;
		return ;
	}
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
	ft_write_msg(philo, SLEEP);
	usleep(philo->infos->time_to_sleep);
	ft_write_msg(philo, THINK);
}

static void	*ft_test(void *arg)
{
	t_philo				*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	//printf("%d\n", philo->infos->time_to_sleep);
	philo->last_meal = ft_get_time();
	//printf("isdead : %d\n", philo->infos->is_dead);
	//printf("isprinted : %d\n", philo->infos->is_printed);
	while (!philo->infos->is_dead && !philo->infos->is_printed)
		ft_eat(philo);
	return (0);
}

int	ft_launch_thread(t_philo *philo, int len, pthread_t *new_thread)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (pthread_create(&new_thread[i], NULL,
				ft_test, &philo[i]) != 0)
			return (ft_free(philo, new_thread, 2));
	}
	i = -1;
	while (++i < len)
	{
		if (pthread_join(new_thread[i], NULL) != 0)
			return (ft_free(philo, new_thread, 2));
	}
	return (1);
}
