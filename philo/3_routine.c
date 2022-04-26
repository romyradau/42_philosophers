# include "philo.h"

int	your_mum_calls(t_philly *philly, t_data *data)
{
	if (get_time() - philly->last_burger >= data->ttd)
	{
		// pthread_mutex_lock(&data->dead_mx);
		print_message(philly, &philly->args, "died");
		// data->dead = true;
		// pthread_mutex_unlock(&data->dead_mx);
		return (1);
	}
	// pthread_mutex_unlock(&data->dead_mx);
	return (0);
}

int	eat(t_philly *philly, t_data *data)
{
	pthread_mutex_lock(&philly->right_fork);
	if (your_mum_calls(philly, data))
	{
		pthread_mutex_unlock(&philly->right_fork);
		// pthread_mutex_unlock(&data->print_mx);
		return (1);
	}
	print_message(philly, &data, "has taken a fork");
	pthread_mutex_lock(philly->left_fork);
	if (your_mum_calls(philly, data))
	{
		pthread_mutex_unlock(&philly->right_fork);
		pthread_mutex_unlock(philly->left_fork);
		// pthread_mutex_unlock(&data->print_mx);
		return (1);
	}
	print_message(philly, &data, "has taken a second fork");
	philly->burgers++;
	philly->last_burger = get_time();
	print_message(philly, &data, "is eating burgers");
	if (sleep_until(data->tte, philly, data))
	{	
		pthread_mutex_unlock(&philly->right_fork);
		pthread_mutex_unlock(philly->left_fork);
		return (1);
	}
	pthread_mutex_unlock(&philly->right_fork);
	pthread_mutex_unlock(philly->left_fork);
	if (your_mum_calls(philly, data))
	{
		return (1);
	}
	return (0);
}

void	nap(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is sleeping");
	sleep_until(data->tts, philly, data);
}

void	think(t_philly *philly, t_data *data)
{
	print_message(philly, &data, "is thinking");
}

void	*routine(void *input)
{
	t_philly *philly;
	int		meals;

	philly = (t_philly *)input;
	meals = philly->args->notephme;
	if (philly->id % 2)
		sleep_until(100, philly, philly->args);//sollte ich hier auch sleep_ms nehmen??
	//ist das nicht irgendwie hin und her
	//man will dass alles gleichzeitig lauft und dann pausiert amna ber
	//nimmt das nicht eigentlich die funktion von threads weg?
	pthread_mutex_lock(&philly->args->dead_mx);
	while (philly->burgers < meals || !philly->args->dead)
	{
		pthread_mutex_unlock(&philly->args->dead_mx);
		//lonely philly missing
		if (meals > -1 && philly->burgers >= meals)
			break;
			//pdf sais at least notephme
		// if (your_mum_calls(philly, philly->args))//mum
		// {
		// 	pthread_mutex_unlock(&philly->args->print_mx);
		// 	break ;
		// }
		//muss man das so mahen?
		//darf ein mutex gelockt bleiben?
		if (eat(philly, philly->args))//mum
			break ;
		nap(philly, philly->args);
		if (your_mum_calls(philly, philly->args))
		{
			// pthread_mutex_unlock(&philly->args->print_mx);
			break ;
		}	
        //du musst immer checken sobald die was machen/gemacht haben
        //bzw wenn die halt gerade gleichzeitig was versuchen
		think(philly, philly->args);
		pthread_mutex_lock(&philly->args->dead_mx);
	}
	pthread_mutex_unlock(&philly->args->dead_mx);
	return (NULL);
}