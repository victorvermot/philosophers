/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:36:21 by vvermot-          #+#    #+#             */
/*   Updated: 2021/12/30 12:43:54 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define EAT 1
# define THINK 2
# define SLEEP 3
# define RED "\033[0;31m"
# define GREEN "\033[0;33m"
# define WHITE "\033[0m"

typedef struct s_time{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_time;

typedef struct s_philo{
	int	id;
	int	last_meal;
	int	left_fork;
	int	right_fork;
}	t_philo;

typedef struct s_thread{
	pthread_t		*new_thread;
	pthread_mutex_t	*fork;
	t_time			*times;
	t_philo			*philo;
}	t_thread;

int		ft_atoi(const char *str);
void	ft_eat(t_thread *thread);
void	ft_sleep(t_thread *thread);
void	ft_think(t_thread *thread);
int		ft_allocate(t_thread *thread, int len, char **argv);
void	ft_free(t_thread *thread, int opt);

#endif