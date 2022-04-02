/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codevault.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 18:51:46 by rschleic          #+#    #+#             */
/*   Updated: 2022/04/02 21:34:14 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	eat = 0;
pthread_mutex_t mutex;

void	*routine()
{
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		//this function waits and locks and does everything
		eat++;
		pthread_mutex_unlock(&mutex);
	}
	// sleep(2);
	// printf("routine	%d\n", x);
	// sleep(3);
	// printf("what you gonna do\n");
}

// void	give_birth()
// 	/*	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(&ph[i], NULL, &routine, NULL) != 0)
// 		//last para is for the args for the function which we dont have yet
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		printf("philosopher	%d starts eating \n", i);
// 	}*/
// void	update()
// 	/*
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_join(ph[i], NULL))
// 		//==wait but for threads, 2nd para == pointer that gets the result from this thread
// 			return (2);
// 		printf("philosopher	%d stops eating\n", i);
// 	}
// 	*/

int	main(int argc, char **argv)
{
	pthread_t ph[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
	//a struct == variable where you cn store info a bout the thread
	for (i = 0; i < 5; i++)
	{
		if (pthread_create(&ph[i], NULL, &routine, NULL) != 0)
		//last para is for the args for the function which we dont have yet
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("philosopher	%d starts eating \n", i);
	}
	for (i = 0; i < 5; i++)
	//es muss < nicht <= sein, sonst geht etwas schief...
	{
		if (pthread_join(ph[i], NULL))
		//==wait but for threads, 2nd para == pointer that gets the result from this thread
			return (2);
		printf("philosopher	%d stops eating\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("ate	%d times\n", eat);
	return (0);
}