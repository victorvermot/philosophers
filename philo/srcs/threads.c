/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:28:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/06 17:56:02 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_death(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->infos->philo_num)
	{
		if (philo[i].is_dead)
			return (0);
	}
	return (1);
}

static int	ft_are_philo_hungry(t_philo *philo)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (philo->infos->time_to_win)
	{
		while (++i < philo->infos->philo_num)
		{
			if (philo[i].meal_count == philo[i].infos->time_to_win)
				count++;
		}
		if (count == philo->infos->philo_num)
			return (0);
	}
	return (1);
}

void	ft_eat(t_philo *philo)
{
	gettimeofday(&philo->c_time, NULL);
	while (philo->c_time.tv_usec - philo->last_meal < philo->infos->time_to_die
		&& ft_check_death(philo->head))
	{
		// printf("%d last meal%d\n", philo->id, philo->c_time.tv_usec - philo->last_meal);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->right_philo->fork);
		ft_write_msg(philo, FORK);
		usleep(philo->infos->time_to_eat);
		ft_write_msg(philo, EAT);
		gettimeofday(&philo->c_time, NULL);
		philo->last_meal = philo->c_time.tv_usec;
		// printf("%d last meal is now %d\n", philo->id, philo->last_meal);
		pthread_mutex_unlock(&philo->right_philo->fork);
		pthread_mutex_unlock(&philo->fork);
		usleep(philo->infos->time_to_sleep);
		ft_write_msg(philo, SLEEP);
		gettimeofday(&philo->c_time, NULL);
		printf("where we at%d\n", philo->c_time.tv_usec - philo->last_meal);
	}
	ft_write_msg(philo, DEATH);
	//if (philo->c_time.tv_usec - philo->last_meal < philo->infos->time_to_die)
	philo->is_dead = 1;
}

static void	*ft_test(void *arg)
{
	t_philo				*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		usleep(90);
	//printf("%d\n", philo->infos->time_to_sleep);
	gettimeofday(&philo->c_time, NULL);
	philo->last_meal = philo->c_time.tv_usec;
	while (ft_are_philo_hungry(philo) && ft_check_death(philo))
	{
		ft_eat(philo);
	}
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
