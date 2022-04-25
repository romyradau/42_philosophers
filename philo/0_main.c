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

void	print_message(t_philly *philly, t_data **data, const char *message)
{
	pthread_mutex_lock(&(*data)->print_mx);
	// printf("%ld	%d	%s\n", )
	// printf("start	%lu	\n", (*data)->start);
	printf("%lu %d %s\n", get_time() - (*data)->start, philly->id, message);
	pthread_mutex_unlock(&(*data)->print_mx);

}

void	sleep_ms(time_t val)
{
	time_t	time;

	time = get_time();
	while (1)
	{
		if (time + val <= get_time())
			break ;
		// time_to_die(philo);
		usleep(100);
	}
}

int	your_mum_calls(t_philly *philly, t_data *data)
{
	pthread_mutex_lock(&data->dead_mx);
	// printf("id: %d time %ld\n",philly->id, get_time());
	// printf("id: %d last burger: %ld\n",philly->id, philly->last_burger);
	// printf("id: %d time - burger: %ld\n",philly->id, data->start - philly->last_burger);
	if (philly->last_burger - data->start > data->ttd)
	{
		print_message(philly, &philly->args, "died");
		philly->dead = true;
		pthread_mutex_unlock(&data->dead_mx);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mx);
	return (0);

}
//figure out whats wrong with your death timing
//but very well doen today <3

int	eat(t_philly *philly, t_data *data)
{
	pthread_mutex_lock(&philly->right_fork);
	print_message(philly, &data, "has taken a fork");
	pthread_mutex_lock(philly->left_fork);
	print_message(philly, &data, "has taken a second fork");
	philly->burgers++;
	sleep_ms(data->tte);
	print_message(philly, &data, "is eating burgers");
	philly->last_burger = get_time();
	pthread_mutex_unlock(&philly->right_fork);
	pthread_mutex_unlock(philly->left_fork);
	if (your_mum_calls(philly, data))
		return (1);
	return (0);
}


void	nap(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is sleeping");
	sleep_ms(data->tts);
}

void	think(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is thinking");
}



void	*routine(void *input)
{
	t_philly *philly;
	int		meals;

	philly = (t_philly *)input;
	meals = philly->args->notephme;
	if (philly->id % 2)
		usleep(100);
	//ist das nicht irgendwie hin und her
	//man will dass alles gleichzeitig lauft und dann pausiert amna ber
	//nimmt das nicht eigentlich die funktion von threads weg?
	while (philly->burgers < meals || !philly->dead)
	{
		if (philly->burgers == meals)
			break;
		if (your_mum_calls(philly, philly->args))
			break ;
		if (eat(philly, philly->args))
			break ;
		nap(philly, philly->args);
		think(philly, philly->args);
	}
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
		if (current->next)
			next_ph = current->next;
		pthread_mutex_destroy(&current->right_fork);
		free(current);
		// current = NULL;
		current = next_ph;
		i--;
	}
	pthread_mutex_destroy(&current->right_fork);
	free(current);
	current = NULL;
	free((*data));
	data = NULL;
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
			//maybe lock print_mx
			printf("failed to join thread\n");
			return (1);
		}
			//welcher fehler soll hier kommen?
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
	}
	//if (pthread_join((*data)->your_mum, NULL) != 0)
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
		//muss theoretischc protected werden
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
	pthread_mutex_init(&(*data)->print_mx, NULL);
		//muss theoretischc protected werden
	pthread_mutex_init(&(*data)->dead_mx, NULL);
		//muss theoretischc protected werden
	(*data)->start = get_time();
	//muss das vor dem thread_cerate passieren doer egal?
	//bei dir davor weil du das data_init nicht lockst
	while (1)
	{
		// head->name = "romy";
		head->dead = false;
		head->id = i;
		head->burgers = 0;
		head->args = (*data);
		head->left_fork = &head->next->right_fork;
		head->last_burger = get_time();
		if (pthread_create(&head->thread, NULL, routine, head) != 0)
		{
			free_phillys(data, (*data)->noph);
			//maybe print_mx
			printf("failed to create thread\n");
			return (1);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
		i++;
	}
	//eine variante hier den waiter_thread einfugen mit anderer routine
	//und dann auch beim joinen
	//if (pthread_create(data->your_mum, NULL, kills_you, data) != 0);
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
		// free(data);
		//reicht doch oder? 
		//weil die ganzen einzelnen werte in data habe ich ja nicht extra gemalloct!?
		return (1);
	}
	if (create_phillys(&data))
	{
		// free(data);
		return (1);
	}
	// print_phillys(data);
	free_phillys(&data, data->noph);
	// if (clear_table(&data))
	// 	//whatever needs to be freed up til here
	// free(data);
	// data = NULL;
	// print_phillys(data);
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
