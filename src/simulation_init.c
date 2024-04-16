/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 14:41:23 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_forks_to_philo(t_setting *data)
{
	int	i;

	i = 0;
	if (data->number_of_philo == 1)
		return ;
	while (i < data->number_of_philo
		&& data->philos[i].next->index != 0)
	{
		if (data->philos[i].index % 2 == 0)
		{
			philo_grab_forks(&data->philos[i]);
			printf("can eat \n");
			data->philos[i].can_eat = true;
		}
		else
			data->philos[i].can_sleep = true;
		i++;
	}
}

int	init_simulation(t_setting *data)//separate the funciton with end_simulation + loop_simulation() inside main funciton
{
	pthread_mutex_t *forks_mutex;

	forks_mutex = NULL;
	if (data->max_meals_set == true)
		pthread_mutex_init(&data->mutex_max_meals, NULL);
	forks_mutex = initialize_mutex(data, forks_mutex);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_exit, NULL);
	set_forks_to_philo(data);
	loop_simulation(data);
	destroy_mutex(data, forks_mutex);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_exit);
	if (data->max_meals_set == true)
		pthread_mutex_destroy(&data->mutex_max_meals);
	free(forks_mutex);
	return (SUCCESS);
}
