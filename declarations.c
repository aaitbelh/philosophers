/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 09:55:46 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/02/23 17:37:28 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_all(t_data *data)
{
	free(data->philo);
	free(data->fork);
	free(data->th);
}

int	max_min(t_data *data)
{
	if (data->n_of_eat > INT_MAX || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX)
	{
		clear_all(data);
		return (0);
	}
	return (1);
}

void	make_all2(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].last_eat = 0;
		data->philo[i].id = i + 1;
		data->philo[i].rightfork = &data->fork[data->philo[i].id
			% data->n_of_philo];
		data->philo[i].liftfork = &data->fork[data->philo[i].id - 1];
		data->philo[i].data = data;
		data->philo[i].is_eating = 0;
		data->philo[i].mode_eat = 0;
		i++;
	}
}

int	make_all(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->n_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->start_of_time = get_time();
	data->lmoot = 1;
	if (ac == 6)
		data->n_of_eat = ft_atoi(av[5]);
	else
		data->n_of_eat = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_of_philo);
	if (!data->fork)
		return (0);
	data->philo = malloc(sizeof(t_philo) * data->n_of_philo);
	if (!data->philo)
		return (0);
	data->th = malloc(sizeof(pthread_t) * data->n_of_philo);
	if (!data->th)
		return (0);
	pthread_mutex_init(&data->io, NULL);
	make_all2(data);
	return (1);
}
