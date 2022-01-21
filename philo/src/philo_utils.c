/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:34:34 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/21 14:32:59 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_write_msg(t_philo *philo, char *opt)
{
	size_t	time;

	time = ft_get_time() - philo->infos->init_time;
	if (!philo->done_eating)
	{
		if (philo->id % 2 == 0)
			printf("%ld" YELLOW " %d %s\n"WHITE, time, philo->id, opt);
		else
			printf("%ld" RED " %d %s\n"WHITE, time, philo->id, opt);
	}
}

size_t	ft_get_time(void)
{
	struct timeval	c_time;

	gettimeofday(&c_time, NULL);
	return ((c_time.tv_sec * 1000) + (c_time.tv_usec / 1000));
}

void	ft_usleep_enhanced(t_philo *philo, size_t time)
{
	size_t	t;

	t = ft_get_time();
	while (!philo->infos->is_dead)
	{
		if ((ft_get_time() - t) >= time)
			break ;
		usleep(100);
	}
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	result;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}
