/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:14:01 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/16 15:05:57 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	args_check(t_time *time, char **argv)
{
	time->time_to_die = ft_atoi(argv[2]);
	time->time_to_eat = ft_atoi(argv[3]);
	time->time_to_sleep = ft_atoi(argv[4]);
}

void	*ft_test(void *arg)
{
	t_time	*time;

	time = arg;
	printf("I run at this micro_seconds : %d\n", time->time_to_die);
	return (0);
}

int	main(int argc, char **argv)
{
	struct timeval	c_time;
	pthread_t		*new_thread;
	t_time			times;
	int				i;
	int				len;

	new_thread = NULL;
	len = ft_atoi(argv[1]);
	i = 0;
	if (argc == 4 || argc == 5)
	{
		new_thread = malloc(sizeof(pthread_t) * len);
		args_check(&times, argv);
		gettimeofday(&c_time, NULL);
		while (i < len)
			pthread_create(&new_thread[i++], NULL, ft_test, &times);
		i = 0;
		while (i < len)
			pthread_join(new_thread[i++], NULL);
		//printf("seconds: %ld\n%d", c_time.tv_sec, c_time.tv_usec);
	}
	return (0);
}
