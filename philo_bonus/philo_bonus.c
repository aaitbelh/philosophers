/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:33:43 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/19 16:59:29 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *x)
{
	t_data	*data;
	size_t	tmp;

	data = (t_data *)x;
	while (1)
	{
		tmp = get_time() - data->time_to_start;
		if (data->much_eat >= data->n_of_eat && data->n_of_eat != -1)
			exit (0);
		if (tmp - data->last_eat >= data->time_to_die && data->mod_eat != 1)
		{
			sem_wait(data->io);
			printf("%lu ms %d is die\n", (get_time()
					- data->time_to_start), data->id);
			exit (1);
		}
		usleep(10);
	}
	return (NULL);
}

void	ft_sleep(t_data *data)
{
	print_output("is sleeping", data);
	smart_sleep(data->time_to_sleep);
	print_output("is thinking", data);
}

void	eat(t_data *data)
{
	sem_wait(data->sema);
	print_output("is taking a fork", data);
	sem_wait(data->sema);
	print_output("is taking a fork", data);
	print_output("is eating", data);
	data->mod_eat = 1;
	data->last_eat = get_time() - data->time_to_start;
	smart_sleep(data->time_to_eat);
	sem_post(data->sema);
	sem_post(data->sema);
	data->much_eat++;
	data->mod_eat = 0;
}

void	philos(t_data *data, int i)
{
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		ft_error("forking failed");
	else if (!data->pid[i])
	{
		data->id = i + 1;
		pthread_create(&data->thread, NULL, &routine, data);
		pthread_detach(data->thread);
		while (1)
		{
			if (data->much_eat >= data->n_of_eat && data->n_of_eat != -1)
				exit(0);
			eat(data);
			ft_sleep(data);
		}
	}
}

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;
	int		ret;

	if ((ac != 5 && ac != 6) || check_errors(av))
		ft_error("ERROR: NOT ENOUGH ARGS OR SOME THINGS RONG");
	data = malloc(sizeof(t_data) * 1);
	if (!make_all(data, ac, av) || !max_min(data))
		ft_error("ERROR: ANY THING WRONG,FOLLOW RULES\n");
	i = -1;
	while (++i < data->n_of_philo)
		philos(data, i);
	i = -1;
	while (i++ < data->n_of_philo)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			wait_kill(data);
			break ;
		}
	}
	free(data->pid);
	free(data);
	return (0);
}
