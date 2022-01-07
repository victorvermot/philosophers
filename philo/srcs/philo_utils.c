/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 10:34:34 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/06 17:30:48 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

void	ft_write_msg(t_philo *philo, int opt)
{
	if (opt == FORK)
	{
		printf("%d "YELLOW"%d "PINK"has "RED"taken "L_BLUE"a "
			D_BLUE"fork\n"WHITE, philo->c_time.tv_usec, philo->id);
	}
	else if (opt == EAT)
	{
		printf("%d "YELLOW"%d "PINK"is "RED"eating "L_BLUE
			"\n"WHITE, philo->c_time.tv_usec, philo->id);
	}
	else if (opt == SLEEP)
	{
		printf("%d "YELLOW"%d "PINK"is "D_BLUE"sleeping "L_BLUE
			"\n"WHITE, philo->c_time.tv_usec, philo->id);
	}
	else if (opt == THINK)
	{
		printf("%d "YELLOW"%d "PINK"is "L_BLUE"thinking "L_BLUE
			"\n"WHITE, philo->c_time.tv_usec, philo->id);
	}
	else if (opt == DEATH)
	{
		printf("%d "YELLOW"%d "RED"died "L_BLUE
			"\n"WHITE, philo->c_time.tv_usec, philo->id);
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