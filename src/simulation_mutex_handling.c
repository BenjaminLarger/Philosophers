/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_mutex_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:30:38 by blarger           #+#    #+#             */
/*   Updated: 2024/04/14 18:58:34 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*initialize_mutex(t_setting *data, pthread_mutex_t *mutex)
{
	int	i;

	mutex = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!mutex)
		return (NULL); //handle malloc failure
	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		data->philos[i].fork.mutex_fork = &mutex[i];
		i++;
	}
	return (mutex);
}

void	destroy_mutex(t_setting *data, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&mutex[i]);
		free(&mutex[i]);
		i++;
	}
}

void	set_death_mutex(t_setting *data)
{
	pthread_mutex_t mutex;

	int	i;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < data->number_of_philo)
	{
		data->philos[i].mutex_death = &mutex;
		i++;
	}
}
