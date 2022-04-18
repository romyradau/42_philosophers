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

void	*routine(t_data *data, t_philly *first_thread)
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

t_philly *philly_cdll(t_data **data)
{
	//function that creates cdll
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	(*data)->first_ph = phil;
	while (i > 0)
	{
		phil = ft_calloc(1, sizeof(t_philly))
		phil = phil->next;
		i--;
	}
	//doesn't need to be protected ft_calloc manages
	//needs the initializition of the fork mutexes
	return ((*data)->first_ph)
}

int	join_phillys(t_data *data, pthread_t *phil)
{
	t_philly	*tmp_ph;

	tmp_ph = data->first_thread
	while (1)
	{
		if (pthread_join(tmp_ph->thread, NULL) != 0)
			return (2);
			//welcher fehler soll hier kommen?
		tmp_ph = tmp_ph->next;
		if (tmp_ph == data->first_ph)
			break ;
	}
	return (0);
}


int	create_phillys(t_data **data)
{
	t_philly	*tmp_ph;

	tmp_ph = philly_cdll()
	//zeigt jetzt auf den ersten
	while (1)
	{
		if (pthread_create(tmp_ph->thread, NULL, &routine, tmp_ph->thread) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		tmp_ph = tmp_ph->next;
		if (tmp_ph == (*data)->first_ph)
			break ;
	}
	if (join_phillys(data, phil))
		return (1);
	// pthread_mutex_destroy(&mutex_fork);
	return (0);
}

int	set_fork_mutexes(t_data **data)
{
	int i;
	int j;


	// pthread_mutex_t fork;
	i = data->noph;
	j = 0;

	while (i > 0)
	{
		//muss ich die forks(mutex) allocaten??
		pthread_mutex_init(fork, NULL);//while == forks
		i--;

	}
		//here just init all the mutexs
		//do i have to do this for every philosopher?
		pthread_mutex_init(phil->prev_fork, NULL);//while == forks
		// pthread_mutex_init(phil->if_dead_no_eat, NULL);//while == forks
}
//nur gabeln und schauen was schief schlagt

int	clear_table(t_data **data)
{
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	phil = (*data)->first_ph;
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
	
	if (input_check(argc))
		return (1);
	//unvollständig
	data = ft_calloc(1, sizeof(t_data));
	//pointer auf data wird gemalloct
	data = init_args(argv);
	//doesn't need to be protected ft_calloc handles
	set_fork_mutexes(data);
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
