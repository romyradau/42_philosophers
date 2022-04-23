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

void	*routine(void *philo)
{
	t_philly *head;

	head = (t_philly *)philo;
	// int		meals;

	// meals = data->notephme;
	// if (data->notephme > 0)
	// {
	// 	while (meals > 0)
	// 	{
	// 		pthread_mutex_lock(head->left_fork);
	// 		pthread_mutex_lock(&head->right_fork);
	// 		//this function waits and locks and does everything
	// 		meals--;
	// 		pthread_mutex_unlock(head->left_fork);
	// 		pthread_mutex_unlock(&head->right_fork);
	// 	}
	// }
	return (NULL);
}
//eat
//sleep...

void	free_phillys(t_data **data, int i)
{
	printf("\n\nFREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n");
	t_philly *current;
	t_philly *next_ph;

	current = (*data)->first_ph;
	while (i > 1)
	{
		printf("current address %p\n", current);
		printf("hallo\n");
		if (current->next)
			next_ph = current->next;
		pthread_mutex_destroy(&current->right_fork);
		free(current);
		// (*data)->first_ph = NULL;
		printf("\nfirst ID %d\n", (*data)->first_ph->id);
		printf("%p\n\n", (*data)->first_ph);
		current = next_ph;
		i--;
	}
	pthread_mutex_destroy(&current->right_fork);
	free(current);
	// (*data)->first_ph = NULL;
	printf("%p\n\n", (*data)->first_ph);
	printf("\n\nFREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n");

}
//freet nicht wies soll ?


int	join_phillys(t_data **data)
{
	t_philly	*head;

	head = (*data)->first_ph;
	while (1)
	{
		if (pthread_join(head->thread, NULL) != 0)
		{
			free_phillys(data, (*data)->noph);
			printf("failed to join thread\n");
			return (1);
		}
			//welcher fehler soll hier kommen?
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
	}
	return (0);
}


t_philly *philly_cdll(t_data **data)
{
	int i;
	t_philly *current;

	i = 1;
	(*data)->first_ph = ft_calloc(1, sizeof(t_philly));
	if (!(*data)->first_ph)
	//null muss ja nicht gefreet werden?!
		return (NULL);
	current = (*data)->first_ph;
	pthread_mutex_init(&current->right_fork, NULL);
	while (i < (*data)->noph)
	{
		current->next = ft_calloc(1, sizeof(t_philly));
		if (!current->next)
		{
			free_phillys(data, i);
			return (NULL);
		}	
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
	if (head == NULL)
		return (1);
	(*data)->start = get_time();
	//muss das vor dem thread_cerate passieren doer egal?
	//bei dir davor weil du das data_init nicht lockst
	while (1)
	{
		// head->name = "romy";
		head->id = i;
		head->args = (*data);
		head->left_fork = &head->next->right_fork;
		if (pthread_create(&head->thread, NULL, &routine, head) != 0)
		{
			free_phillys(data, (*data)->noph);
			printf("failed to create thread\n");
			return (1);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
		i++;
	}
	if (join_phillys((data)))
		return (1);
	// pthread_mutex_destroy(&mutex_fork);
	return (0);
}

// int	clear_table(t_data **data)
// {
// 	int	i;
// 	t_philly *phil;
	
// 	i = (*data)->noph;
// 	phil = (*data)->first_ph;
// 	while (i > 0)
// 	{
// 		pthread_mutex_destroy(phil->left_fork);//while == forks
// 		pthread_mutex_destroy(&phil->right_fork);//while == forks
// 		phil = phil->next;
// 	}
// 	return (0);
// }

void	print_phillys(t_data *data)
{
	int i;
	t_philly *current;

	i = 0;
	current = data->first_ph; //current besser
	while (i < data->noph) // i = 0 < number_philos statt while(1) && break
	{
		printf("id	%d\n", current->id);
		printf("data pointer	%p\n", current->args);
		printf("right fork	%p\n", &current->right_fork);
		printf("left fork	%p\n", current->left_fork);
		printf("own address	%p\n", current);
		printf("next philo	%p\n", current->next);
		if (current->next)
			current = current->next;
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (input_check(argc, argv))
		return (1);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (1);
	if (init_args(argv, data) == 1)
	{
		free(data);
		//reicht doch oder? 
		//weil die ganzen einzelnen werte in data habe ich ja nicht extra gemalloct!?
		return (1);
	}
	if (create_phillys(&data))
	{
		free(data);
		return (1);
	}
	print_phillys(data);
	free_phillys(&data, data->noph);
	// if (clear_table(&data))
	// 	//whatever needs to be freed up til here
	free(data);
	print_phillys(data);
	// fscanf(stdin, "c");
	return (0);
}
/*
argv[0] == number_of_philosophers
argv[1] == time_to_die
argv[2] == time_to_eat
argv[3] == time_to_sleep
argv[4] == [number_of_times_each_philosopher_must_eat]
*/
