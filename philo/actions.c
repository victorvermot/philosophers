/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:59:44 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/17 17:47:34 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Chaque philosopheur devrait carry son time de dernier meal

void	ft_eat(t_thread *thread)
{
	pthread_mutex_lock(&thread->fork);
	usleep(thread->times->time_to_eat);
	pthread_mutex_unlock(&thread->fork);
	ft_sleep(thread);
}

void	ft_sleep(t_thread *thread)
{
	usleep(thread->times->time_to_sleep);
	ft_think(thread);
}

void	ft_think(t_thread *thread)
{
	(void)thread;
	//ft_eat(thread);
}
