/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:37:41 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/02/25 15:39:21 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct t_data
{
	u_int64_t		start_of_time;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_die;
	u_int64_t		time_to_sleep;
	int				n_of_eat;
	int				n_of_philo;
	struct s_philo	*philo;
	pthread_mutex_t	io;
	int				lmoot;
	pthread_mutex_t	*fork;
	pthread_t		*th;
}	t_data;

typedef struct s_philo
{
	int					id;
	u_int64_t			last_eat;
	int					is_eating;
	int					mode_eat;
	pthread_mutex_t		*liftfork;
	pthread_mutex_t		*rightfork;
	struct t_data		*data;
}	t_philo;

int			exit_error(char *str);
int			ft_strlen(char *str);
int			ft_atoi(const char *str);
int			check_errors(char **av);
int			make_all(t_data *data, int ac, char **av);
u_int64_t	get_time(void);
void		smart_sleep(unsigned long t, t_philo *philo);
void		manager(t_data *data);
void		print_output(char *str, t_philo *philo);
void		clear_all(t_data *data);
int			max_min(t_data *data);

#endif