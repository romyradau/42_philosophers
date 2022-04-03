/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:32:29 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/02 21:48:06 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

//int	pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(start_routine)(void *), void *arg)
//creates a new thread of execution

void	*love(void *arg)
{
	for (int i = 0; i < 4; i++)
	{
		sleep(1);
		printf("she loves me  \n");
	}
	printf("she loves me !!! \n");
	return (NULL);
}

void	no_love()
{
	for (int i = 0; i < 3; i++)
	{
		sleep(1);
		printf("she loves me not \n");
	}
}

int	main()
{
	pthread_t newthread;
	
	pthread_create(&newthread, NULL, &love, NULL);
	//&newthread keeps track of the thread i just create
	// myturn();
	no_love();
	pthread_join(newthread, NULL);
	//waits until a specific thread finishes running
}
