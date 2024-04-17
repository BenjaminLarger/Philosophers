/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:51 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 12:28:46 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	update_variable_state_after_eating(t_philo *philos_copy)
{
	philos_copy->last_meal = current_time_stamp_in_ms();
	printf("%d last eat set %lld\n", philos_copy->index, philos_copy->last_meal);
	unlock_mutex(&philos_copy->mutex_last_meal);
	philos_copy->meals_eaten++;
	printf("meals eaten = %d\n", philos_copy->meals_eaten);
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
			print_state_change(EATS, philos_copy->index, philos_copy, true);
			lock_mutex(&philos_copy->mutex_last_meal);
			usleep(philos_copy->data->time_to_eat);
			update_variable_state_after_eating(philos_copy);
			update_if_philo_has_reached_max_meals(philos);
		}
		if (philos_copy->can_eat == false)
		{
			print_state_change(SLEEP, philos_copy->index, philos_copy, true);
			usleep(philos_copy->data->time_to_sleep);
			print_state_change(THINKS, philos_copy->index, philos_copy, true);
			if (philo_grab_forks(philos_copy) == SUCCESS)
				philos_copy->can_eat = true;
		}
		//check_if_a_philo_must_exit(philos_copy);
	}
	return (SUCCESS);
}
void	loop_simulation(t_setting *data)
{
	int				i;
	pthread_t		*threads;

	threads = malloc(sizeof(pthread_t) * data->number_of_philo);
	if (!threads)
		return (free_data_print_error_and_exit(MALLOC, 2, data));
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&threads[i], NULL, &philos_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD_CREATE,
					EXIT_FAILURE, data));
		i++;
	}
	printf("enter in function loop\n");
	constant_check_table(data, threads);
	i = 0;
	/* while (i < data->number_of_philo)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN,
					EXIT_FAILURE, data));
		i++;
	} */
	printf("done joining philos\n");
	free(threads);
}
