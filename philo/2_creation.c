/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_creation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschleic <rschleic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:54:40 by rschleic          #+#    #+#             */
/*   Updated: 2022/05/03 20:15:10 by rschleic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_phillys(t_data **data)
{
	t_philly	*head;

	head = (*data)->first_ph;
	while (1)
	{
		if (pthread_join(head->thread, NULL) != 0)
		{
			free_phillys(data, (*data)->noph);
			printf("failed to join thread\n");
			return (1);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
	}
	return (0);
}

int	new_philly(t_data **data, t_philly	**current, int i)
{
	while (i < (*data)->noph)
	{
		(*current)->next = ft_calloc(1, sizeof(t_philly));
		if (!(*current)->next)
		{
			free_phillys(data, i);
			return (1);
		}	
		(*current) = (*current)->next;
		if (pthread_mutex_init(&(*current)->right_fork, NULL) != 0)
		{
			free((*current));
			free_phillys(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

t_philly	*philly_cdll(t_data **data)
{
	int			i;
	t_philly	*current;

	i = 1;
	(*data)->first_ph = ft_calloc(1, sizeof(t_philly));
	if (!(*data)->first_ph)
		return (NULL);
	current = (*data)->first_ph;
	if (pthread_mutex_init(&current->right_fork, NULL) != 0)
	{
		free ((*data)->first_ph);
		return (NULL);
	}
	if (new_philly(data, &current, i))
		return (NULL);
	current->next = (*data)->first_ph;
	return ((*data)->first_ph);
}

int	init_philly(t_data **data)
{
	t_philly	*head;	
	int			i;

	i = 1;
	head = (*data)->first_ph;
	while (1)
	{
		head->id = i;
		head->burgers = 0;
		head->args = (*data);
		head->left_fork = &head->next->right_fork;
		head->last_burger = get_time();
		head->right = true;
		head->left = &head->next->right;
		if (pthread_create(&head->thread, NULL, &routine, head) != 0)
		{
			free_phillys(data, (*data)->noph);
			return (2);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
		i++;
	}
	return (0);
}

int	create_phillys(t_data **data)
{
	t_philly	*head;

	(*data)->created_all = false;
	head = philly_cdll(data);
	if (head == NULL)
		return (1);
	if (pthread_mutex_init(&(*data)->print_mx, NULL) != 0)
		return (2);
	if (pthread_mutex_init(&(*data)->dead_mx, NULL) != 0)
		return (2);
	(*data)->start = get_time();
	(*data)->dead = false;
	if (init_philly(data))
		return (2);
	(*data)->created_all = true;
	if (join_phillys(data))
		return (2);
	return (0);
}
