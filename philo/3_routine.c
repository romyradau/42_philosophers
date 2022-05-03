/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_routine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 20:15:20 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/03 20:44:00 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_right_fork(t_philly *philly, t_data *data)
{
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&philly->right_fork);
		if (philly->right)
		{
			philly->right = false;
			print_message(philly, &data, "has taken a fork");
			pthread_mutex_unlock(&philly->right_fork);
			break ;
		}	
		pthread_mutex_unlock(&philly->right_fork);
		if (your_mum_calls(philly, data))
			return (1);
	}
	return (0);
}

int	wait_for_left_fork(t_philly *philly, t_data *data)
{
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(philly->left_fork);
		if (*(philly->left))
		{
			print_message(philly, &data, "has taken a second fork");
			*(philly->left) = false;
			pthread_mutex_unlock(philly->left_fork);
			break ;
		}	
		pthread_mutex_unlock(philly->left_fork);
		if (your_mum_calls(philly, data))
			return (1);
	}
	return (0);
}	

int	eat(t_philly *philly, t_data *data)
{
	if (wait_for_right_fork(philly, data))
		return (1);
	if (wait_for_left_fork(philly, data))
		return (1);
	philly->burgers++;
	philly->last_burger = get_time();
	print_message(philly, &data, "is eating burgers");
	if (add_time(data->tte, philly, data))
		return (1);
	pthread_mutex_lock(philly->left_fork);
	*(philly->left) = true;
	pthread_mutex_unlock(philly->left_fork);
	pthread_mutex_lock(&philly->right_fork);
	philly->right = true;
	pthread_mutex_unlock(&philly->right_fork);
	return (0);
}

int	nap(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is sleeping");
	if (add_time(data->tts, philly, data))
		return (1);
	return (0);
}

void	think(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is thinking");
}
