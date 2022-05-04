/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:30:20 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/04 11:38:51 by rschleic         ###   ########.fr       */
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

int	your_mum_calls(t_philly *philly, t_data *data)
{
	pthread_mutex_lock(&data->dead_mx);
	if (get_time() - philly->last_burger >= data->ttd)
	{
		pthread_mutex_unlock(&data->dead_mx);
		print_message(philly, &philly->args, "died");
		return (1);
	}
	pthread_mutex_unlock(&data->dead_mx);
	return (0);
}

void	wait_and_go(t_data *data, t_philly *philly)
{
	pthread_mutex_lock(&data->init_mx);
	while (data->created_all == false)
	{
		pthread_mutex_unlock(&data->init_mx);
		usleep(100);
		pthread_mutex_lock(&data->init_mx);
	}
	pthread_mutex_unlock(&data->init_mx);
	if (philly->id % 2 == 0)
		add_time(data->tte - 10, philly, data);
}

void	*routine(void *input)
{
	t_philly	*philly;
	int			meals;

	philly = (t_philly *)input;
	wait_and_go(philly->args, philly);
	meals = philly->args->notephme;
	pthread_mutex_lock(&philly->args->dead_mx);
	while ((philly->burgers < meals || !philly->args->dead))
	{
		pthread_mutex_unlock(&philly->args->dead_mx);
		if (meals > -1 && philly->burgers >= meals)
			break ;
		if (eat(philly, philly->args))
			break ;
		if (nap(philly, philly->args))
			break ;
		think(philly, philly->args);
		pthread_mutex_lock(&philly->args->dead_mx);
	}
	pthread_mutex_unlock(&philly->args->dead_mx);
	return (NULL);
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
		return (1);
	if (create_phillys(&data) == 1)
	{
		free(data);
		data = NULL;
		return (1);
	}
	else
	{
		system("leaks philo");
		pthread_mutex_destroy(&data->print_mx);
		pthread_mutex_destroy(&data->dead_mx);
		free_phillys(&data, data->noph);
		free(data);
		data = NULL;
		return (0);
	}
}
