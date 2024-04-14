/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:51 by blarger           #+#    #+#             */
/*   Updated: 2024/04/14 19:01:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			print_state_actualization(EATS, philos_copy->index, philos_copy);
			philos_copy->last_meal = current_time_stamp_in_ms();
			usleep(philos_copy->time_to_eat);
			philo_drop_forks(philos_copy);
			philos_copy->can_eat = false;
		}
		else if (philos_copy->can_eat == false)
		{
			print_state_actualization(SLEEP, philos_copy->index, philos_copy);
			usleep(philos_copy->time_to_sleep);
			if (philo_must_die(philos_copy) == true)
				philos_copy->is_dead = true;//we enter more than once in philo must die !!!
			print_state_actualization(THINKS, philos_copy->index, philos_copy);
			if (philo_grab_forks(philos_copy) == SUCCESS)
				philos_copy->can_eat = true;
		}
		if (philos_copy->is_dead == true)
		{
			printf("WE MUST EXIT THE LOOP\n");
			break ;
		}
	}
	return (NULL);
}

void	loop_simulation(t_setting *data)
{
	int	i;
	pthread_t		thread[data->number_of_philo];

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&thread[i], NULL, &philos_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD_CREATE, EXIT_FAILURE, data));
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN, EXIT_FAILURE, data));
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_detach(thread[i]) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN, EXIT_FAILURE, data));
		i++;
	}
	printf("WE HAVE EXITED THE LOOP\n");
}
