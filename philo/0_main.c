/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:30:20 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/03 17:57:45 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include "philo.h"

void	*routine(t_data *data, t_philly		*first_thread)
{
	int		meals;

	meals = data->notephme;
	if (data->notephme)
	{
		while (meals > 0)
		{
			pthread_mutex_lock(first_thread->left_fork);
			pthread_mutex_lock(first_thread->right_fork);
			//this function waits and locks and does everything
			meals--;
			pthread_mutex_unlock(first_thread->left_fork);
			pthread_mutex_unlock(first_thread->right_fork);
		}
		if (meals == 0)
			//success
	}
}
//eat
//sleep...

int	join_phillys(t_data *data, pthread_t *phil)
{
	int	i;

	i = data->noph;
	while (i > 0)
	{
		if (pthread_join(phil[i], NULL) != 0)
			return (2);
			//welcher fehler soll hier kommen?
		i--;
	}
	return (0);
}


int	create_phillys(t_data *data)
{
	int				i;
	t_philly		*phil;
	
	i = data->noph;
	phil = data->first_thread;
	// linked list create 
	

	while (i > 0)
	{
		if (pthread_create(phil->thread, NULL, &routine, phil) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		i--;
	}
	if (join_phillys(data, phil))
		return (1);
	// pthread_mutex_destroy(&mutex_fork);
	return (0);
}

int	set_table(t_data **data)
{
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	phil = (*data)->first_thread;
	while (i > 0)
	{
		pthread_mutex_init(phil->left_fork, NULL);//while == forks
		pthread_mutex_init(phil->right_fork, NULL);//while == forks
		pthread_mutex_init(phil->if_dead_no_eat, NULL);//while == forks
		phil = phil->next;
	}
}

int	clear_table(t_data **data)
{
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	phil = (*data)->first_thread;
	while (i > 0)
	{
		pthread_mutex_destroy(phil->left_fork);//while == forks
		pthread_mutex_destroy(phil->right_fork);//while == forks
		pthread_mutex_destroy(phil->if_dead_no_eat);//while == forks

		phil = phil->next;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	data = ft_calloc(1, sizeof(t_data));
	//pointer auf data wird gemalloct
	data = init_args(argv);
	//doesn't need to be protected ft_calloc handles
	if (input_check(argc))
		return (1);
	//checks argc
	set_table(&data);
	if (create_phillys(&data))
		return (1);
	clear_table(&data);
	free(data);
	return (0);
}
/*
argv[0] == number_of_philosophers
argv[1] == time_to_die
argv[2] == time_to_eat
argv[3] == time_to_sleep
argv[4] == [number_of_times_each_philosopher_must_eat]
*/