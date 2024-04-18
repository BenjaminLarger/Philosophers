/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:51 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 11:18:06 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state_change_eating(const char *msg, int philo_i,
			t_philo *philo, bool check_table) //return failure to quit ?
{
	long long	time_to_print;

	lock_mutex(&philo->mutex_last_meal);
	if (check_table == true)
	{
		lock_mutex(&philo->data->can_write);
		if (philo->data->must_exit == true)//use mutex here
		{
			unlock_mutex(&philo->data->can_write);
			return ;
		}
		unlock_mutex(&philo->data->can_write);
	}
	time_to_print = current_time_stamp_in_ms()
		- philo->data->program_time_start;
	printf("%lldms\t\tphilo %d\t\t%s", time_to_print, philo_i, msg);
	ft_usleep(philo->data->time_to_eat);
	philo->last_meal = current_time_stamp_in_ms();
	unlock_mutex(&philo->mutex_last_meal);	
}

static void	update_variable_state_after_eating(t_philo *philos_copy)
{
	philos_copy->meals_eaten++;
	philo_drop_forks(philos_copy);
	philos_copy->can_eat = false;
}

/* 
Common error return values for pthread_mutex_lock include:
* EINVAL: The mutex is invalid.
* EAGAIN: The mutex could not be acquired because it was already locked by another thread.
* EDEADLK: The calling thread already owns the mutex (deadlock situation).
 */
static void	*philos_routine(void *philos)
{
	struct s_philo	*philos_copy;

	philos_copy = (struct s_philo *)philos;
	while (true)
	{
		if (philos_copy->can_eat == true)
		{
			print_state_change_eating(EATS, philos_copy->index, philos_copy, true);
			update_variable_state_after_eating(philos_copy);
			update_if_philo_has_reached_max_meals(philos);
		}
		if (philos_copy->can_eat == false)
		{
			print_state_change(SLEEP, philos_copy->index, philos_copy, true);
			ft_usleep(philos_copy->data->time_to_sleep);
			print_state_change(THINKS, philos_copy->index, philos_copy, true);
			if (philo_grab_forks(philos_copy) == SUCCESS)
				philos_copy->can_eat = true;
		}
		if (check_if_a_philo_must_exit(philos_copy) == true)
		{
			if (philos_copy->can_eat == true)
				philo_drop_forks(philos_copy);
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}
int	loop_simulation(t_setting *data)
{
	int				i;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	if (!threads)
		return (free_print_error_and_return(MALLOC, FAILURE, data));
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&threads[i], NULL, &philos_routine, &data->philos[i]))
			return (free_print_error_and_return(THREAD_CREATE,
					FAILURE, data));
		i++;
	}
	constant_check_table(data, threads);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (free_print_error_and_return(THREAD_JOIN,
					FAILURE, data));
		i++;
	}
	printf("done joining philos\n");
	free(threads);
	return (SUCCESS);
}
