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


long	ft_atoi(const char *str)
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
			return (sign * output);
		else if (sign == 1 && output > INT_MAX)
			return (sign * output);
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
		printf("malloc failed\n");
		return (ptr);
	}
	while (counter < count * size)
	{
		((char *)ptr)[counter] = 0;
		counter++;
	}
	return (ptr);
}

// void	ft_bzero(void *s, size_t n)
// {
// 	size_t	counter;

// 	counter = 0;
// 	while (counter < n)
// 	{
// 		((char *)s)[counter] = '\0';
// 		counter++;
// 	}
// }