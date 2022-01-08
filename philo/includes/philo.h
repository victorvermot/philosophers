/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:36:21 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/07 13:03:41 by vvermot-         ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define THINK "is thinking"
# define SLEEP "is sleeping"
# define DEATH "died"
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
	int	is_printed;
}	t_info;

typedef struct s_philo{
	int				id;
	int				last_meal;
	int				is_dead;
	int				meal_count;
	int				done_eating;
	struct s_philo	*right_philo;
	struct s_philo	*head;
	struct timeval	c_time;
	pthread_mutex_t	fork;
	t_info			*infos;
}	t_philo;

int		ft_atoi(const char *str);
void	ft_eat(t_philo *philo);
int		ft_args_check(t_info *info, char **argv, int opt);
int		ft_allocate(t_philo **philo, pthread_t **new_thread,
			t_info *info, int len);
int		ft_free(t_philo *philo, pthread_t *new_thread, int opt);
void	ft_write_msg(t_philo *philo, char *opt);
int		ft_launch_thread(t_philo *philo, int len, pthread_t *new_thread);

#endif