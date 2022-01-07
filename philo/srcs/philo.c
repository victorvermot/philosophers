/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:14:01 by vvermot-          #+#    #+#             */
/*   Updated: 2022/01/06 12:12:04 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		*new_thread;
	t_info			info;
	int				len;

	philo = NULL;
	if (argc != 5 && argc != 6)
		return (0);
	if (argc == 6)
		ft_args_check(&info, argv, 1);
	else
		ft_args_check(&info, argv, 0);
	len = ft_atoi(argv[1]);
	if (len <= 0)
		return (0);
	if (!ft_allocate(&philo, &new_thread, &info, len))
		return (0);
	printf("%d\n", info.time_to_win);
	if (!ft_launch_thread(philo, len, new_thread))
		return (0);
	return (0);
}
