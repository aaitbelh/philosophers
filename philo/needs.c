/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 09:48:51 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/02/21 14:04:20 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_output(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->io);
	if (philo->data->lmoot)
		printf("%llu ms %d %s\n",
			(get_time() - philo->data->start_of_time), philo->id, str);
	pthread_mutex_unlock(&philo->data->io);
}

void	smart_sleep(unsigned long t, t_philo *philo)
{
	unsigned long long	start;

	start = get_time();
	while (philo->data->lmoot)
	{
		if (get_time() - start >= t)
			break ;
		usleep(300);
	}
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						sig;
	unsigned long long int	n;

	sig = 1;
	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
		if (n >= 9223372036854775807 && sig == 1)
			return (-1);
		if (n > 9223372036854775807 && sig == -1)
			return (0);
	}
	return ((int)(n * sig));
}
