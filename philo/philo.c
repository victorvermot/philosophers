/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:14:01 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/17 17:45:14 by vvermot-         ###   ########.fr       */
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
	t_thread	*threads;

	threads = arg;
	ft_eat(threads);
	printf("I run at this micro_seconds : %d\n", threads->times->time_to_die);
	return (0);
}

int	main(int argc, char **argv)
{
	t_thread		threads;
	int				i;
	int				len;

	if (argc == 4 || argc == 5)
	{
		len = ft_atoi(argv[1]);
		i = 0;
		threads.new_thread = malloc(sizeof(pthread_t) * len);
		args_check(threads.times, argv);
		//gettimeofday(&c_time, NULL);
		if (pthread_mutex_init(&threads.fork, NULL) != 0)
		{
			free(threads.new_thread);
			return (0);
		}
		while (i < len)
			if (pthread_create(&threads.new_thread[i++], NULL, ft_test, &threads) != 0)
			{
				free(threads.new_thread);
				return (0);
			}
		i = 0;
		while (i < len)
			pthread_join(threads.new_thread[i++], NULL);
		//printf("seconds: %ld\n%d", c_time.tv_sec, c_time.tv_usec);
		pthread_mutex_destroy(&threads.fork);
	}
	return (0);
}
