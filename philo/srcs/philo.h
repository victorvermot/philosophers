/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:36:21 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/05 18:15:17 by vvermot-         ###   ########.fr       */
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

# define FORK 0
# define EAT 1
# define THINK 2
# define SLEEP 3
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define D_BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define L_BLUE "\033[0;36m"
# define BLACK "\033[0;30m"
# define WHITE "\033[0m"

typedef struct s_info{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_win;
	int	philo_num;
}	t_info;

typedef struct s_philo{
	int				id;
	int				last_meal;
	int				is_dead;
	struct s_philo	*right_philo;
	struct timeval	c_time;
	pthread_mutex_t	id_mutex;
	pthread_mutex_t	fork;
	t_info			*infos;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
int		ft_args_check(t_info *info, char **argv, int opt);
int		ft_allocate(t_philo **philo, pthread_t **new_thread,
			t_info *info, int len);
int		ft_free(t_philo *philo, pthread_t *new_thread, int opt);
void	ft_write_msg(t_philo *philo, int opt);
int		ft_launch_thread(t_philo *philo, int len, pthread_t *new_thread);

#endif