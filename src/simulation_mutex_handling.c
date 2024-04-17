/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_mutex_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:30:38 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 11:42:31 by blarger          ###   ########.fr       */
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
