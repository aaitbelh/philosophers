/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declare_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:32:07 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/16 01:21:31 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	make_all(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->n_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->last_eat = 0;
	data->mod_eat = 0;
	data->much_eat = 0;
	data->pid = malloc(sizeof(int ) * data->n_of_philo);
	if (!data->pid)
		return (0);
	if (ac == 6)
		data->n_of_eat = ft_atoi(av[5]);
	else
		data->n_of_eat = -1;
	sem_unlink("sema");
	data->sema = sem_open("sema", O_CREAT, 0644, data->n_of_philo);
	sem_unlink("io");
	data->io = sem_open("io", O_CREAT, 0644, 1);
	data->time_to_start = get_time();
	return (1);
}
