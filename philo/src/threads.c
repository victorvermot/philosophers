/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:28:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/21 14:53:18 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	hold_door(t_philo *p)
{
	int	i;
	int	count;

	while (!p->infos->done_eating)
	{
		i = -1;
		count = 0;
		while (++i < p->infos->philo_num)
		{
			if (ft_get_time() - p[i].last_meal > (size_t)p->infos->time_to_die)
			{
				ft_write_msg(p, DEATH);
				p->infos->is_dead = 1;
				return ;
			}
			if (p->done_eating)
				count++;
		}
		if (count == p->infos->philo_num)
		{
			printf("Philosophers are done eating\n");
			p->infos->done_eating = 1;
			return ;
		}
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_write_msg(philo, FORK);
	pthread_mutex_lock(&philo->right_philo->fork);
	ft_write_msg(philo, FORK);
	pthread_mutex_lock(&philo->infos->mutex_print);
	ft_write_msg(philo, EAT);
	pthread_mutex_unlock(&philo->infos->mutex_print);
	ft_usleep_enhanced(philo, philo->infos->time_to_eat);
	pthread_mutex_lock(&philo->infos->mutex_count);
	philo->meal_count += 1;
	if (philo->meal_count == philo->infos->time_to_win)
		philo->done_eating = 1;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->infos->mutex_count);
	pthread_mutex_unlock(&philo->right_philo->fork);
	pthread_mutex_unlock(&philo->fork);
}

static void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->infos->is_dead)
	{
		ft_eat(philo);
		ft_write_msg(philo, SLEEP);
		ft_usleep_enhanced(philo, philo->infos->time_to_sleep);
		ft_write_msg(philo, THINK);
	}
	return (0);
}

int	ft_launch_thread(t_philo *philo, int philo_num, pthread_t *new_thread)
{
	int	i;

	i = -1;
	while (++i < philo_num)
	{
		if (pthread_create(&new_thread[i], NULL,
				ft_philo, &philo[i]) != 0)
			return (ft_free(philo, new_thread, 2));
		philo[i].last_meal = ft_get_time();
	}
	return (1);
}
