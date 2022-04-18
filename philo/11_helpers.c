/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:10:27 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/03 19:38:52 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_args(char **argv)
{
	t_data	args;
	
	args.noph = ft_atoi(argv[1]);
	args.ttd = ft_atoi(argv[1]);
	args.tte = ft_atoi(argv[2]);
	args.tts = ft_atoi(argv[3]);
	
	return (&args);
}

int	input_check(int x)
{
	if (x > 5)
	{
		printf("too many arguments\n");
		return (1);
	}
	if (x < 4)
	{
		printf("too few arguments\n");
		return (1);
	}
	return (0);
}
//which input is also wrong?

int	ft_atoi(const char *str)
{
	int		counter;
	long	output;
	int		sign;

	counter = 0;
	output = 0;
	sign = 1;
	while (str[counter] == 32 || (str[counter] <= 13 && str[counter] >= 9))
		counter++;
	if (str[counter] == '-')
	{
		sign = -1;
		counter++;
	}
	else if (str[counter] == '+')
		counter++;
	while (str[counter] >= '0' && str[counter] <= '9')
	{
		output = output * 10 + str[counter++] - '0';
		if (sign == -1 && output > (long) INT_MAX + 1)
			return (-1);
		else if (sign == 1 && output > INT_MAX)
			return (-2);
	}
	return (sign * output);
}


void	*ft_calloc(size_t count, size_t size)
{
	size_t	counter;
	void	*ptr;

	counter = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		write(2, "ERROR: malloc failed\n", 22);
		exit(1);
	}
	while (counter < count * size)
	{
		((char *)ptr)[counter] = 0;
		counter++;
	}
	return (ptr);
}