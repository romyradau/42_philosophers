#include "philo.h"


void	free_phillys(t_data **data, int i)
{
	printf("\n\nFREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n");
	t_philly *current;
	t_philly *next_ph;

	current = (*data)->first_ph;
	while (i > 1)
	{
		if (current->next)
			next_ph = current->next;
		pthread_mutex_destroy(&current->right_fork);
		free(current);
		// current = NULL;
		current = next_ph;
		i--;
	}
	pthread_mutex_destroy(&current->right_fork);
	free(current);
	current = NULL;
	free((*data));
	data = NULL;
	printf("\n\nFREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n\n");

}
//freet nicht wies soll - oder doch?
//wie kann ich das richtig sichtbar machen ?

int	clear_table(t_data **data)
{
	int	i;
	t_philly *phil;
	
	i = (*data)->noph;
	phil = (*data)->first_ph;
	while (1)
	{
		pthread_mutex_destroy(&phil->right_fork);
		//muss auch protectd werden
		phil = phil->next;
		if (phil->next == (*data)->first_ph)
			break ;
	}
	return (0);
}

int	join_phillys(t_data **data)
{
	t_philly	*head;

	head = (*data)->first_ph;
	while (1)
	{
		if (pthread_join(head->thread, NULL) != 0)
		{
			free_phillys(data, (*data)->noph);
			//maybe lock print_mx
			printf("failed to join thread\n");
			return (1);
		}
			//welcher fehler soll hier kommen?
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
	}
	//if (pthread_join((*data)->your_mum, NULL) != 0)
	return (0);
}


t_philly *philly_cdll(t_data **data)
{
	int i;
	t_philly *current;

	i = 1;
	(*data)->first_ph = ft_calloc(1, sizeof(t_philly));
	if (!(*data)->first_ph)
	//null muss ja nicht gefreet werden?!
		return (NULL);
	current = (*data)->first_ph;
	pthread_mutex_init(&current->right_fork, NULL);
	while (i < (*data)->noph)
	{
		current->next = ft_calloc(1, sizeof(t_philly));
		if (!current->next)
		{
			free_phillys(data, i);
			return (NULL);
		}	
		current = current->next;
		pthread_mutex_init(&current->right_fork, NULL);
		//muss theoretischc protected werden
		i++;
	}
	current->next = (*data)->first_ph;
	return ((*data)->first_ph);
}


int	create_phillys(t_data **data)
{
	t_philly	*head;
	int			i;

	i = 1;
	head = philly_cdll(data);
	if (head == NULL)
		return (1);
	pthread_mutex_init(&(*data)->print_mx, NULL);
		//muss theoretischc protected werden
	pthread_mutex_init(&(*data)->dead_mx, NULL);
		//muss theoretischc protected werden
	(*data)->start = get_time();
	//muss das vor dem thread_cerate passieren doer egal?
	//bei dir davor weil du das data_init nicht lockst
	(*data)->dead = false;
	(*data)->right = true;
	(*data)->left = true;
	while (1)
	{
		// head->name = "romy";
		head->id = i;
		head->burgers = 0;
		head->args = (*data);
		head->left_fork = &head->next->right_fork;
		head->last_burger = get_time();
		if (pthread_create(&head->thread, NULL, routine, head) != 0)
		{
			free_phillys(data, (*data)->noph);
			//maybe print_mx
			printf("failed to create thread\n");
			return (1);
		}
		head = head->next;
		if (head == (*data)->first_ph)
			break ;
		i++;
	}
	//eine variante hier den waiter_thread einfugen mit anderer routine
	//und dann auch beim joinen
	//if (pthread_create(data->your_mum, NULL, kills_you, data) != 0);
	if (join_phillys((data)))
		return (1);
	// pthread_mutex_destroy(&mutex_fork);
	return (0);
}