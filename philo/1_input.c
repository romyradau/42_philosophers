/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 12:41:43 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/29 12:41:46 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	max_min_check(t_data *data)
{
	if (data->noph > INT_MAX || data->noph < INT_MIN)
	{
		printf("wrong input\n");
		return (1);
	}
	else if (data->ttd > INT_MAX || data->ttd < INT_MIN)
	{
		printf("wrong input\n");
		return (1);
	}
	else if (data->tte > INT_MAX || data->tte < INT_MIN)
	{
		printf("wrong input\n");
		return (1);
	}
	else if (data->tts > INT_MAX || data->tts < INT_MIN)
	{
		printf("wrong input\n");
		return (1);
	}
	else if (data->notephme > INT_MAX || data->notephme < INT_MIN)
	{
		printf("wrong input\n");
		return (1);
	}
	return (0);
}

int	init_args(char **argv, t_data *data)
{	
	data->noph = ft_atol(argv[1]);
	data->ttd = ft_atol(argv[2]);
	data->tte = ft_atol(argv[3]);
	data->tts = ft_atol(argv[4]);
	if (argv[5])
		data->notephme = ft_atol(argv[5]);
	else
		data->notephme = -1;
	if (max_min_check(data) == 1)
		return (1);
	return (0);
}

int	input_check(int x, char **argv)
{
	int i;
	int j;

	i = 1;
	if (x < 5 || x > 6)
	{
		printf("wrong number of arguments\n");
		return (1);
	}
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' && argv[i][j + 1] != '\0')
			j++;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < 48 || argv[i][j] > 57 || argv[i][0] == '0')
			{
				printf("non numeric or no argument\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
//was passeirt denn bei einer 0 ?
