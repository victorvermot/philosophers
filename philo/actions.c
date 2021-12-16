/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:59:44 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/16 15:13:17 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_time *time)
{
	usleep(time->time_to_eat);
	ft_sleep(time);
}

void	ft_sleep(t_time *time)
{
	usleep(time->time_to_sleep);
	ft_think(time);
}

void	ft_think(t_time *time)
{
	(void)time;
}
