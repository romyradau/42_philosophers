/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:06:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/30 14:10:45 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include "philo.h"

typedef struct s_data
{
	long			noph;
	time_t			start;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	long			notephme;
	bool			dead;
	bool			right;
	bool			left;
	pthread_mutex_t	dead_mx;
	pthread_mutex_t print_mx;
	struct s_philly		*first_ph;
}	t_data;

typedef struct s_philly
{
	t_data			*args;
	int				id;
	int				burgers;
	time_t			last_burger;
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	struct s_philly	*next;
}	t_philly;

int		input_check(int x, char **argv);
void	*ft_calloc(size_t count, size_t size);
int		init_args(char **argv, t_data *data);
long	ft_atol(const char *str);
time_t	get_time(void);

int		create_phillys(t_data **data);
void	*routine(void *input);
int		sleep_until(time_t time, t_philly *philly, t_data *data);
int		your_mum_calls(t_philly *philly, t_data *data);
int		print_message(t_philly *philly, t_data **data, const char *message);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		clear_table(t_data **data);
void	free_phillys(t_data **data, int i);

#endif