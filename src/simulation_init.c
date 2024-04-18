/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 12:34:36 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialize_mutex(t_setting *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->philos[i].mutex_fork, NULL);
		pthread_mutex_init(&data->philos[i].mutex_last_meal, NULL);
		if (data->max_meals_set == true)
			pthread_mutex_init(&data->philos[i].mutex_max_meal_reach, NULL);
		i++;
	}
}

void	destroy_mutex(t_setting *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->philos[i].mutex_fork);
		pthread_mutex_destroy(&data->philos[i].mutex_last_meal);
		if (data->max_meals_set == true)
			pthread_mutex_destroy(&data->philos[i].mutex_max_meal_reach);
		i++;
	}
}

int	init_simulation(t_setting *data)
{
	data->time_to_think = (data->time_to_eat * 2) - data->time_to_sleep;
	initialize_mutex(data);
	pthread_mutex_init(&data->mutex_grab_forks, NULL);
	pthread_mutex_init(&data->can_write, NULL);
	data->program_time_start = current_time_stamp_in_ms();
	if (loop_simulation(data) == FAILURE)
		return (FAILURE);
	destroy_mutex(data);
	pthread_mutex_destroy(&data->mutex_grab_forks);
	pthread_mutex_destroy(&data->can_write);
	return (SUCCESS);
}
