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
# include "philo.h"

typedef struct s_philly
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*if_dead_no_eat;
	t_data			*args;
	t_philly		*next;
}	t_philly;

typedef struct s_data
{
	int				noph;
	int				ttd;
	int				tte;
	int				tts;
	int				notephme;
	pthread_mutex_t	*forks;
	//array mit anzahl von threads
	t_philly		*first_thread;
}	t_data;

// typedef struct s_mutex
// {
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// 	pthread_mutex_t	dead;
// }	t_mex;

#endif