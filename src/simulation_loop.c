/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:51 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 16:23:47 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	update_variable_state_after_eating(t_philo *philos_copy)
{
	philos_copy->last_meal = current_time_stamp_in_ms();
	philos_copy->meals_eaten++;
	unlock_mutex(&philos_copy->data->mutex_death);
	unlock_mutex(&philos_copy->data->mutex_max_meals);
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
			//printf("waiting for eat %d\n", philos_copy->index);
			lock_mutex(&philos_copy->data->mutex_max_meals);
			lock_mutex(&philos_copy->data->mutex_death);
			//printf("done waiting for eat %d\n", philos_copy->index);
			print_state_change(EATS, philos_copy->index, philos_copy, false);
			usleep(philos_copy->data->time_to_eat);
			update_variable_state_after_eating(philos_copy);
			if (update_if_philo_has_reached_max_meals(philos) == true)
			{
				return (SUCCESS);
			}
		}
		if (philos_copy->can_eat == false)
		{
			print_state_change(SLEEP, philos_copy->index, philos_copy, true);
			usleep(philos_copy->data->time_to_sleep);
			print_state_change(THINKS, philos_copy->index, philos_copy, true);
			if (philo_grab_forks(philos_copy) == SUCCESS)
				philos_copy->can_eat = true;
		}
		if (check_if_a_philo_must_exit(philos_copy) == true)
		{
			philo_drop_forks(philos_copy);
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}
void	loop_simulation(t_setting *data)
{
	int				i;
	pthread_t		thread[data->number_of_philo];//create malloc here

	/* thread = malloc(sizeof(pthread_t) * data->number_of_philo);
	if (!thread)
		return (free_data_print_error_and_exit(MALLOC, 2, data)
			, NULL) ; */
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&thread[i], NULL, &philos_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD_CREATE,
					EXIT_FAILURE, data));
		i++;
	}
	printf("enter in function loop\n");
	constant_check_table(data);
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN,
					EXIT_FAILURE, data));
		i++;
	}
	printf("done joining philos\n");
}
