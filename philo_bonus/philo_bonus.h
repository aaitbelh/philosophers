/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:32:20 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/15 00:56:37 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <pthread.h>
# include <signal.h>
# include <limits.h>

typedef struct s_data
{
	int			*pid;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		time_to_die;
	size_t		time_to_start;
	int			n_of_philo;
	uint64_t	last_eat;
	int			n_of_eat;
	int			id;
	sem_t		*sema;
	int			lmoot;
	int			mod_eat;
	sem_t		*io;
	sem_t		*stop;
	sem_t		*death;
	pthread_t	thread;
	int			much_eat;
	int			i;
}	t_data;

int		make_all(t_data *data, int ac, char **av);
int		check_errors(char **av);
void	print_output(char *str, t_data *data);
size_t	get_time(void);
void	smart_sleep(unsigned long t);
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	wait_kill(t_data *data);
int		max_min(t_data *data);
#endif