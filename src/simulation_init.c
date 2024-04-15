/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/15 16:23:36 by blarger          ###   ########.fr       */
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

int	init_simulation(t_setting *data)
{
	pthread_mutex_t *forks_mutex;
	pthread_mutex_t *death_mutex;

	forks_mutex = NULL;
	death_mutex = NULL;
	forks_mutex = initialize_mutex(data, forks_mutex);
	death_mutex = initialize_mutex(data, death_mutex);
	pthread_mutex_init(&data->mutex_death, NULL);
	set_forks_to_philo(data);
	loop_simulation(data);
	//check_if_philo_died();
	destroy_mutex(data, forks_mutex);
	destroy_mutex(data, death_mutex);
	free(data->philos->fork.mutex_fork);
	return (SUCCESS);
}
