/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:41:19 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/02 22:10:57 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void	*bitches_money()
{
	int	value = (rand() % 1000000) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	printf("pointer_address_in_thread:	%p\n", result);
	return (void *) result;
}
//damit kann das ergebnis in join zuruck gegeben werden
//free!!! but not in here

int	main(int argc, char **argv)
{
	int	*res;
	srand(time(NULL));
	pthread_t philly;
	if (pthread_create(&philly, NULL, &bitches_money, NULL) != 0)
	{
		return (1);
	}
	if (pthread_join(philly, (void **) &res) != 0)
	{
		return (2);
	}
	printf("pointer_address_in_main:	%p\n", res);
	printf("soon your bank acount will look like this	%d $\n", *res);
	free(res);
	return (0);
}

//normally one wants to allocate and deallocate in the same function
//improvement for that will follow!