/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 12:28:40 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



int	init_simulation(t_setting *data)//separate the funciton with end_simulation + loop_simulation() inside main funciton
{
	pthread_mutex_t *forks_mutex;
	pthread_mutex_t *last_meal_mutex;
	pthread_mutex_t *max_meal_reach;

	data->time_to_think = (data->time_to_eat * 2) - data->time_to_sleep;
	printf("time to sleep = %d\n", data->time_to_sleep);
	forks_mutex = NULL;
	last_meal_mutex = NULL;
	max_meal_reach = NULL;
	/* if (data->max_meals_set == true)
		pthread_mutex_init(&data->mutex_max_meals, NULL); */
	initialize_mutex(data);
	//pthread_mutex_init(&data->mutex_must_exit, NULL);
	pthread_mutex_init(&data->mutex_grab_forks, NULL);
	pthread_mutex_init(&data->can_write, NULL);
	data->program_time_start = current_time_stamp_in_ms();
	//set_forks_to_philo(data);
	if (loop_simulation(data) == FAILURE)
		return (FAILURE);
	destroy_mutex(data);
	//pthread_mutex_destroy(&data->mutex_must_exit);
	pthread_mutex_destroy(&data->mutex_grab_forks);
	pthread_mutex_destroy(&data->can_write);
	/* if (data->max_meals_set == true)
		pthread_mutex_destroy(&data->mutex_max_meals); */
	free(forks_mutex);
	free(last_meal_mutex);
	free(max_meal_reach);
	return (SUCCESS);
}
