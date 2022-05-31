/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:32:07 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/16 16:25:00 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->rightfork);
	print_output("is taking a fork", philo);
	if (philo->rightfork == philo->liftfork)
		return ;
	pthread_mutex_lock(philo->liftfork);
	print_output("is taking a fork", philo);
	philo->mode_eat = 1;
	print_output("is eating", philo);
	philo->last_eat = get_time() - philo->data->start_of_time;
	smart_sleep(philo->data->time_to_eat, philo);
	philo->is_eating++;
	philo->mode_eat = 0;
	pthread_mutex_unlock(philo->liftfork);
	pthread_mutex_unlock(philo->rightfork);
}

void	*routine(void *d)
{
	t_philo	*philo;

	philo = (t_philo *)d;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->data->lmoot)
	{
		if (philo->data->n_of_eat != -1
			&& philo->is_eating >= philo->data->n_of_eat)
			break ;
		eat(philo);
		if (philo->data->n_of_eat != -1
			&& philo->is_eating >= philo->data->n_of_eat)
			break ;
		if (philo->rightfork == philo->liftfork)
			return (NULL);
		print_output("is sleeping", philo);
		smart_sleep(philo->data->time_to_sleep, philo);
		print_output("is thinking", philo);
	}
	return (NULL);
}

int	mush_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_of_philo)
	{
		if (data->philo[i].is_eating == data->n_of_eat)
			return (1);
		i++;
	}
	return (0);
}

void	manager(t_data *data)
{	
	int			i;
	u_int64_t	tmp;

	while (1)
	{
		i = 0;
		while (i < data->n_of_philo)
		{
			tmp = get_time() - data->start_of_time;
			if (tmp - data->philo[i].last_eat >= data->time_to_die
				&& data->philo[i].mode_eat != 1)
			{
				data->lmoot = 0;
				pthread_mutex_lock(&data->io);
				printf("%llu ms %d is die\n", get_time()
					- data->start_of_time, data->philo[i].id);
				pthread_mutex_unlock(&data->io);
				return ;
			}
			i++;
		}
		if (mush_eat(data))
			break ;
	}
}

int	main(int ac, char **av)
{
	int		i;
	t_data	data;

	i = 0;
	if ((ac != 5 && ac != 6) || !check_errors(av))
		return (exit_error("ERROR: NOT ENOUGH ARGS OR SOME THINGS RONG\n"));
	if (!make_all(&data, ac, av) || !max_min(&data))
		return (exit_error("ERROR: ANY THING WRONG ON ARGUMENT,FOLLOW RULES\n"));
	while (i < data.n_of_philo)
	{
		if (pthread_create(&data.th[i], NULL, &routine, &data.philo[i]) != 0)
			return (exit_error("ERROR IN THE CREATING THREADS"));
		i++;
	}
	manager(&data);
	i = 0;
	while (i < data.n_of_philo)
	{
		if (pthread_join(data.th[i], NULL))
			return (exit_error("ERROR WITH JOING THREADS"));
		i++;
	}
	clear_all(&data);
	return (0);
}
