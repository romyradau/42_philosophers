# include "philo.h"

int	your_mum_calls(t_philly *philly, t_data *data)
{
	//hier dead_mx locken, dann brauchst du keien ready to eat!
	// pthread_mutex_lock(&data->dead_mx);
	//vlt muss man das nicht locken, weile s philly spezifisch ist
	//und ttd nciht verdnert wird
	if (get_time() - philly->last_burger >= data->ttd)
	{
		// pthread_mutex_unlock(&data->dead_mx);
		print_message(philly, &philly->args, "died");
		// data->dead = true;
		return (1);
	}
	// pthread_mutex_unlock(&data->dead_mx);
	return (0);
}

int	ready_to_eat(t_philly *philly, t_data *data, char c)
{
	if (c == 'r')
	{
		//gibts hier nen problem mit 
		//dass der andere nie deie gabel nehmen kann
		//weil der mutex gleich hier verwednet wird?
		pthread_mutex_lock(&philly->right_fork);//impro variante mit extra lock bool
		if (your_mum_calls(philly, data))
		{
			pthread_mutex_unlock(&philly->right_fork);
			// pthread_mutex_unlock(&data->print_mx);
			return (1);
		}
		pthread_mutex_unlock(&philly->right_fork);//impro variante mit extra lock bool
		return (0);
	}
	//so wird right jetzt unlocked, wenn die gabel genommen wurde
	//man braucht keine extra fuction hier
	else if (c == 'l')
	{
		pthread_mutex_lock(philly->left_fork);//impro variante mit extra lock bool
		if (your_mum_calls(philly, data))
		{
			// pthread_mutex_unlock(&philly->right_fork);
			pthread_mutex_unlock(philly->left_fork);
			// pthread_mutex_unlock(&data->print_mx);
			return (1);
		}
		pthread_mutex_unlock(philly->left_fork);
	}
	return (0);
}

int	eat(t_philly *philly, t_data *data)
{
	//die sterben beim warten auf die erste gabel
	//die warten so lange 
	// bool left_fork_taken;
	// bool right_fork_taken; 
	// left_fork_taken = false;
	// right_fork_taken = false;
	while (1) // find out if right fork is available, if it is -> take it
	{
		pthread_mutex_lock(&philly->right_fork); // lock boolean for the right fork check
		if (philly->right) // actual check for the right fork
		{
			philly->right = false; // taking the fork -> right fork is not available anymore so we set it to false
			print_message(philly, &data, "has taken a fork");
			// right_fork_taken = true;
			pthread_mutex_unlock(&philly->right_fork); // unlock boolean for the right fork check, now other threads will see the fork as not available
			break ;
		}	
		pthread_mutex_unlock(&philly->right_fork);
		//check if I died
		//extra mutex um das zu checken
		if (your_mum_calls(philly, data))
			return (1);
		//fuck muss jetzt hier right unlocked werden oder nicht, wenn mand ie gabel nehmen konnte?
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
		if (*(philly->left))
		{
			print_message(philly, &data, "has taken a second fork");
			*(philly->left) = false;
			// left_fork_taken = true;
			pthread_mutex_unlock(philly->left_fork);
			break ;
		}	
		pthread_mutex_unlock(philly->left_fork);
		if (your_mum_calls(philly, data))
			return (1);
	}
	//ab dem moment ist nichts gelockt
	//das ist doch ein problem??
	//wenn ich hier jetzt einfach den dead mutex drum amche
	//gibt das probleme ? weil z.b. jmd anderes den benutzt?
	//ich check das noch nciht
	// pthread_mutex_lock(&data->dead_mx);
	// if (left_fork_taken && right_fork_taken)
	// {
	// 	// pthread_mutex_lock(&data->dead_mx);
	// 	// if (philly->last_burger + data->tte > data->ttd)
	// 	// {
	// 	// 	pthread_mutex_unlock(&data->dead_mx);
	// 	// 	your_mum_calls(philly, data);
	// 	// 	return (1);
	// 	// }
	// 	//TODO:bevor die zeit drauf gerechent wird uss geschaut werden ob man dabei sterben würde
	// 	left_fork_taken = false;
	// 	right_fork_taken = false;
		//jede variable muss immer mit dem gleichen mutex gelockt werden!
		//also links mit links und rechts mit rechts
		//TODO: darf das erst anch dem incrementen und timen unlocked werden?
	philly->burgers++;
	philly->last_burger = get_time();
	if (your_mum_calls(philly, data))
	{
		return (1);
	}
	print_message(philly, &data, "is eating burgers");
	// pthread_mutex_unlock(&data->dead_mx);
	if (add_time(data->tte, philly, data))
	{	
		// pthread_mutex_unlock(&philly->right_fork);
		// pthread_mutex_unlock(philly->left_fork);
		//wurden diese beiden zeilen ehen wenn ich beim fork nehmen klappt nicht unlocken wurde?
		return (1);
	}
	pthread_mutex_lock(philly->left_fork);//impro variante mit extra lock bool
	*(philly->left) = true;
	pthread_mutex_unlock(philly->left_fork);//impro variante mit extra lock bool
	pthread_mutex_lock(&philly->right_fork);//impro variante mit extra lock bool
	philly->right = true; // taking the fork -> right fork is not available anymore so we set it to false
	pthread_mutex_unlock(&philly->right_fork);//impro variante mit extra lock bool
	// }
	// we have checked for both forks
	// if we took both forks -> eat -> put down the forks -> return from this subroutine/function
	/* eat:
		1. set ate timestamp to current time
		//2. check if we would die during eating (time to eat > time to die)
		3. sleep until time to die
		4. dead?
	*/
//nach dem essen mussen die right & left weider freigegeben werden!!!!

	// check if we died
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
	if (add_time(data->tts, philly, data))
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
		add_time(100, philly, philly->args);//sollte ich hier auch sleep_ms nehmen??
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