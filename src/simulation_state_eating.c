/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_state_eating.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:33:34 by blarger           #+#    #+#             */
/*   Updated: 2024/04/13 19:13:41 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*eating_routine(void *philos)
{
	struct s_philo	*philos_copy;

	philos_copy = (struct s_philo *)philos;
	pthread_mutex_lock(philos_copy->fork.mutex_ptr);
	usleep(philos_copy->time_to_eat);
	philos_copy->is_eating = false;
	philos_copy->is_sleeping = true;
	return (NULL);
}


void	make_philos_eat(t_setting *data)
{
	int	i;
	pthread_t		thread[8];
	pthread_mutex_t mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < data->number_of_philo)
	{
		data->philos[i].fork.mutex_ptr = &mutex;
		if (data->philos[i].is_eating == true
			&& a_philo_is_dead(data) == false)
		{
			if (pthread_create(&thread[i],
				NULL, &eating_routine, &data->philos[i]))
				return (free_data_print_error_and_exit(THREAD, EXIT_FAILURE, data));
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD, EXIT_FAILURE, data));
		i++;
	}
	pthread_mutex_destroy(&mutex);
}

