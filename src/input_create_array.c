/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_create_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:51:05 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 11:38:18 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	create_philosopher(t_setting *data, int index)
{
	t_philo	philo;

	philo.meals_eaten = 0;
	philo.index = index;
	philo.next = NULL;
	philo.prev = NULL;
	philo.is_dead = false;
	philo.can_eat = false;
	philo.can_sleep = false;
	philo.can_think = false;
	philo.max_meals_reach = false;
	philo.must_exit = false;
	philo.last_meal = current_time_stamp_in_ms();
	philo.data = data;
	return (philo);
}

t_philo	*create_philos_array(t_setting *data)
{
	int				i;
	pthread_mutex_t mutex_death;

	data->philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!data->philos)
		print_error_and_exit(MALLOC, EXIT_FAILURE);
	data->philos = malloc(sizeof(t_philo) * (data->number_of_philo));
    if (!data->philos)
    	return (free_data_print_error_and_exit(MALLOC, 1, data), NULL);
	pthread_mutex_init(&mutex_death, NULL);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i] = create_philosopher(data, i);
		if (data->number_of_philo == 1)
			return (data->philos);
		if (i > 0)
			data->philos[i].prev = &data->philos[i - 1];
		if (i < data->number_of_philo - 1)
			data->philos[i].next = &data->philos[i + 1];
		i++;
	}
	data->philos[0].prev = &data->philos[data->number_of_philo - 1];
	data->philos[i - 1].next = &data->philos[0];
	return (data->philos);
}
