/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_mutex_handling.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:30:38 by blarger           #+#    #+#             */
/*   Updated: 2024/04/16 14:55:42 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t	*initialize_mutex(t_setting *data, pthread_mutex_t *mutex)
{
	int	i;

	mutex = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!mutex)
		return (free_data_print_error_and_exit(MALLOC, 2, data)
			, NULL) ;
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
		i++;
	}
}
