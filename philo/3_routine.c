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

int	ready_to_eat(t_philly *philly, t_data *data, char c)
{
	if (c == 'r')
	{
		pthread_mutex_lock(&philly->right_fork);//impro variante mit extra lock bool
		data->right = true;
		if (your_mum_calls(philly, data))
		{
			pthread_mutex_unlock(&philly->right_fork);
			// pthread_mutex_unlock(&data->print_mx);
			return (1);
		}
		// pthread_mutex_unlock(&philly->right_fork);//impro variante mit extra lock bool
		return (0);
	}
	else if (c == 'l')
	{
		pthread_mutex_lock(philly->left_fork);//impro variante mit extra lock bool
		data->left = true;
		if (your_mum_calls(philly, data))
		{
			pthread_mutex_unlock(&philly->right_fork);
			pthread_mutex_unlock(philly->left_fork);
			// pthread_mutex_unlock(&data->print_mx);
			return (1);
		}
	}
	return (0);
}

int	eat(t_philly *philly, t_data *data)
{
	//die sterben beim warten auf die erste gabel
	//die warten so lange 
	bool left_fork_taken = false;
	bool right_fork_taken = false;
	while (1) // find out if right fork is available, if it is -> take it
	{
		pthread_mutex_lock(&philly->right_fork); // lock boolean for the right fork check
		if (data->right) // actual check for the right fork
		{
			print_message(philly, &data, "has taken a fork");
			data->right = false; // taking the fork -> right fork is not available anymore so we set it to false
			right_fork_taken = true;
			pthread_mutex_unlock(&philly->right_fork); // unlock boolean for the right fork check, now other threads will see the fork as not available
			break ;
		}	
		pthread_mutex_unlock(&philly->right_fork);
		if (ready_to_eat(philly, data, 'r'))
			return (1);
	}
	// pthread_mutex_lock(&philly->right_fork);//impro variante mit extra lock bool
	// if (your_mum_calls(philly, data))
	// {
	// 	pthread_mutex_unlock(&philly->right_fork);
	// 	// pthread_mutex_unlock(&data->print_mx);
	// 	return (1);
	// }

	// pthread_mutex_lock(philly->left_fork);//impro variante mit extra lock bool
	// if (your_mum_calls(philly, data))
	// {
	// 	pthread_mutex_unlock(&philly->right_fork);
	// 	pthread_mutex_unlock(philly->left_fork);
	// 	// pthread_mutex_unlock(&data->print_mx);
	// 	return (1);
	// }
	while (1) // check if left fork is available, if it is -> take it
	{
		pthread_mutex_lock(philly->left_fork);
		if (data->left)
		{
			print_message(philly, &data, "has taken a second fork");
			data->left = false;
			left_fork_taken = true;
			pthread_mutex_unlock(philly->left_fork);
			break ;
		}	
		pthread_mutex_unlock(philly->left_fork);
		if (ready_to_eat(philly, data, 'l'))
			return (1);
	}
	// we have checked for both forks
	// if we took both forks -> eat -> put down the forks -> return from this subroutine/function
	/* eat:
		1. set ate timestamp to current time
		2. check if we would die during eating (time to eat > time to die)
		3. sleep until time to die
		4. dead.
	*/

	// check if we died

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

int	nap(t_philly *philly, t_data *data)
{
	/* check if the time to sleep would be greater than the time to die:
		to sleep: 10s
		to die: 7s
		time to eat: 5s
		time to sleep > time to die -> sleep for time to die -> dead
	*/
	print_message(philly, &data, "is sleeping");
	if (sleep_until(data->tts, philly, data))
		return (1);
	return (0);
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
			//braucht man das if uberhaupt?
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
		if (nap(philly, philly->args))
			break ;
        //du musst immer checken sobald die was machen/gemacht haben
        //bzw wenn die halt gerade gleichzeitig was versuchen
		think(philly, philly->args);
		if (your_mum_calls(philly, philly->args))
		{
			// pthread_mutex_unlock(&philly->args->print_mx);
			break ;
		}	
		pthread_mutex_lock(&philly->args->dead_mx);
	}
	pthread_mutex_unlock(&philly->args->dead_mx);
	return (NULL);
}