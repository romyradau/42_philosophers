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

// void	*routine(t_data *data, t_philly *first_thread)
// {
// 	int		meals;

// 	meals = data->notephme;
// 	if (data->notephme > 0)
// 	{
// 		while (meals > 0)
// 		{
// 			pthread_mutex_lock(first_thread->left_fork);
// 			pthread_mutex_lock(&first_thread->right_fork);
// 			//this function waits and locks and does everything
// 			meals--;
// 			pthread_mutex_unlock(first_thread->left_fork);
// 			pthread_mutex_unlock(&first_thread->right_fork);
// 		}
// 	}
// }
//eat
//sleep...

int	join_phillys(t_data *data)
{
	t_philly	*tmp_ph;

	tmp_ph = data->first_ph;
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

t_philly *philly_cdll(t_data **data)
{
	int i;
	t_philly *current;

	i = 0;
	(*data)->first_ph = ft_calloc(1, sizeof(t_philly));
	//gescheit protecten
	current = (*data)->first_ph;
	pthread_mutex_init(&current->right_fork, NULL);
	while (i < (*data)->noph - 1)
	{
		current->next = ft_calloc(1, sizeof(t_philly));
		current = current->next;
		pthread_mutex_init(&current->right_fork, NULL);
		i++;
	}
	current->next = (*data)->first_ph;
	return ((*data)->first_ph);
}


int	create_phillys(t_data **data)
{
	t_philly	*head;
	int			i;

	i = 1;
	head = philly_cdll(data);
	//zeigt jetzt auf den ersten
	while (1)
	{
		head->id = i;
		head->args = (*data);
		head->left_fork = head->next->right_fork;
		if (pthread_create(&current->thread, NULL, &routine, current->thread) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
	}
	if (join_phillys((*data)))
		return (1);
	// pthread_mutex_destroy(&mutex_fork);
	return (0);
}

//init phillys
//cdll phillys
//free phillys - 1)struct malloc 2)die ganzen values?

int	clear_table(t_data **data)
{
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	phil = (*data)->first_ph;
	while (i > 0)
	{
		pthread_mutex_destroy(phil->left_fork);//while == forks
		pthread_mutex_destroy(&phil->right_fork);//while == forks
		phil = phil->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (input_check(argc, argv))
		return (1);
	//unvollständig
	data = ft_calloc(1, sizeof(t_data));
	//pointer auf data wird gemalloct
	if (init_args(argv, data) == 1)
	{
		free(data);
		return (1);
	}
	//doesn't need to be protected ft_calloc handles
	// set_fork_mutexes(data);
	if (create_phillys(&data))
		return (1);
	if (clear_table(&data))
		//whatever needs to be freed up til here
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
