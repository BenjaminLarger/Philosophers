/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:51 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 10:00:51 by blarger          ###   ########.fr       */
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
			print_state_actualization(EATS, philos_copy->index, philos_copy, true);
			usleep(philos_copy->data->time_to_eat);
			philos_copy->last_meal = current_time_stamp_in_ms();
			philos_copy->meals_eaten++;
			philo_drop_forks(philos_copy);
			philos_copy->can_eat = false;
			printf("%d meals eaten : %d\n", philos_copy->index, philos_copy->meals_eaten);
			if (philos_copy->meals_eaten == philos_copy->data->max_time_to_eat)
			{
				printf("%d is done eating -> stop\n", philos_copy->index);
				philos_copy->max_meals_reach = true;
				break ;
			}
		}
		if (philos_copy->can_eat == false)
		{
			print_state_actualization(SLEEP, philos_copy->index, philos_copy, true);
			usleep(philos_copy->data->time_to_sleep);
			if (philo_must_die(philos_copy) == true)
				break ;
			print_state_actualization(THINKS, philos_copy->index, philos_copy, true);
			if (philo_grab_forks(philos_copy) == SUCCESS)
				philos_copy->can_eat = true;
		}
		if (check_if_a_philo_must_exit(philos_copy) == true)
		{
			printf("has EXIT %d\n", philos_copy->index);
			return (SUCCESS) ;
		}
	}
	printf("\thas EXIT %d\n", philos_copy->index);
	return (SUCCESS);
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
	/* i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_detach(thread[i]) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN, EXIT_FAILURE, data));
		i++;
	} */
}
