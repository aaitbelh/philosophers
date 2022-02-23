/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:02:30 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/02/23 13:57:39 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_errors(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!((av[i][j] >= '0' && av[i][j] <= '9') || av[i][j] == '+'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	exit_error(char *str)
{
	write (2, str, strlen(str));
	return (EXIT_FAILURE);
}
