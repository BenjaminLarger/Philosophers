/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_create_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:51:05 by blarger           #+#    #+#             */
/*   Updated: 2024/04/13 18:53:24 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	create_philosopher(t_setting *data, int index)
{
	t_philo	philo;

	philo.meals_eaten = 0;
	philo.index = index;
	philo.next = NULL;
	philo.prev = NULL;
	philo.fork.is_available = true;
	philo.is_dead = false;
	philo.is_eating = false;
	philo.is_sleeping = false;
	philo.is_thinking = false;
	philo.time_to_die = data->time_to_die;
	philo.time_to_eat = data->time_to_eat;
	philo.time_to_sleep = data->time_to_sleep;
	philo.program_time_start = data->program_time_start;
	return (philo);
}

/* void	link_philosophers(t_philo *philo, t_philo *philo_next)
{
	philo->next = philo_next;
	philo_next->prev = philo;
	philo->is_sleeping = false;
	philo->is_eating = false;
	philo->is_dead = false;
	philo->is_thinking = false;
} */

t_philo	*create_simulation(t_setting *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * (data->number_of_philo));
    if (!data->philos)
        return (NULL);
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
