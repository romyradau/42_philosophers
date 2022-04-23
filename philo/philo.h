/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:06:03 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/03 17:53:23 by rschleic         ###   ########.fr       */
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
# include "philo.h"

typedef struct s_data
{
	long			noph;
	time_t			start;
	time_t			ttd;
	time_t			tte;
	time_t			tts;
	long			notephme;
	int				threads_num;
	// pthread_mutex_t	*forks;
	pthread_mutex_t	dead_mx;
	pthread_mutex_t print_mx;
	//array mit anzahl von threads
	struct s_philly		*first_ph;
}	t_data;

typedef struct s_philly
{
	pthread_t		thread;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	struct s_philly	*next;
	t_data			*args;
	int				id;
}	t_philly;


// typedef struct s_mutex
// {
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// 	pthread_mutex_t	dead;
// }	t_mex;

void	*ft_calloc(size_t count, size_t size);
long	ft_atoi(const char *str);
int		input_check(int x, char **argv);
int		init_args(char **argv, t_data *data);
time_t	get_time(void);
#endif