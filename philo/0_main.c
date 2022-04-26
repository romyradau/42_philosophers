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

#include "philo.h"

int	print_message(t_philly *philly, t_data **data, const char *message)
{
	pthread_mutex_lock(&(*data)->print_mx);
	pthread_mutex_lock(&(*data)->dead_mx);
	if ((*data)->dead)
	{
		pthread_mutex_unlock(&(*data)->dead_mx);
		pthread_mutex_unlock(&(*data)->print_mx);
		return (1);
	}
	pthread_mutex_unlock(&(*data)->dead_mx);
	if (!ft_strncmp(message, "died", 4))
	{
		pthread_mutex_lock(&(*data)->dead_mx);
		(*data)->dead = true;
		pthread_mutex_unlock(&(*data)->dead_mx);
		printf("%lu %d %s\n", get_time() - (*data)->start, philly->id, message);
		pthread_mutex_unlock(&(*data)->print_mx);
		return (1);
	}
	else
	{
		printf("%lu %d %s\n", get_time() - (*data)->start, philly->id, message);
		pthread_mutex_unlock(&(*data)->print_mx);
	}
	return (0);
}

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
	if (clear_table(&data))
	free_phillys(&data, data->noph);
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
