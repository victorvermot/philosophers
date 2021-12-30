/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:14:01 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/30 12:43:57 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_test(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	id_update;
	static int		i;

	// ft_eat(threads);
	pthread_mutex_lock(&id_update);
	i = 0;
	philo = arg;
	// printf("%d\n", i);
	philo->id = i++;
	// printf("Here is my id : %d\n", philo->id);
	pthread_mutex_unlock(&id_update);
	return (0);
}

int	main(int argc, char **argv)
{
	t_thread		threads;
	int				i;
	int				len;

	if (argc != 5 && argc != 6)
		return (0);
	len = ft_atoi(argv[1]);
	if (len <= 0)
		return (0);
	if (!ft_allocate(&threads, len, argv))
		return (0);
	i = -1;
	//gettimeofday(&c_time, NULL);
	while (++i < len)
	{
		if (pthread_mutex_init(&threads.fork[i], NULL) != 0
			|| pthread_create(&threads.new_thread[i], NULL,
				ft_test, &threads.philo[i]) != 0)
		{
			ft_free(&threads, 3);
			return (0);
		}
	}
	i = 0;
	while (i < len)
	{
		printf(RED"%d"WHITE, threads.philo[i].id);
		pthread_join(threads.new_thread[i++], NULL);
	}
	//printf("seconds: %ld\n%d", c_time.tv_sec, c_time.tv_usec);
	pthread_mutex_destroy(threads.fork);
	return (0);
}
