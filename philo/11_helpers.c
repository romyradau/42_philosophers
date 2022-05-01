/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:10:27 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/01 18:55:54 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	add_time(time_t time, t_philly *philly, t_data *data)
{
	time_t	snapshot;

	snapshot = get_time();
	while (1)
	{
		if (snapshot + time <= get_time())
			break ;
		if (your_mum_calls(philly, data))
			return (1);
		usleep(100);
	}
	return (0);
}

time_t	get_time(void)
{
	struct timeval	time;
	time_t			stamp;

	gettimeofday(&time, NULL);
	stamp = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (stamp);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	counter = 0;
	if (n == 0)
		return (0);
	while (counter + 1 < n && a[counter] != '\0' && a[counter] == b[counter])
		counter++;
	return (a[counter] - b[counter]);
}

long	ft_atol(const char *str)
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
