/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:21:45 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/17 18:45:38 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	max_min(t_data *data)
{
	if (data->n_of_eat > INT_MAX || data->time_to_die > INT_MAX
		|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX)
	{
		free(data->pid);
		return (0);
	}
	return (1);
}

void	wait_kill(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_of_philo)
		kill(data->pid[i], SIGKILL);
}

void	print_output(char *str, t_data *data)
{
	size_t	val;

	val = get_time() - data->time_to_start;
	sem_wait(data->io);
	printf("%lu ms %d %s\n", val, data->id, str);
	sem_post(data->io);
}
