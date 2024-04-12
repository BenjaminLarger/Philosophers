/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_create_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:51:05 by blarger           #+#    #+#             */
/*   Updated: 2024/04/12 13:15:13 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*create_philosopher(t_setting *data, int	index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		free_list_until_index(data, index);
		return (print_error_and_exit(MALLOC, EXIT_FAILURE), NULL);
	}
	philo->index = index;
	philo->next = NULL;
	philo->prev = NULL;
	philo->fork.is_available = true;
	return (philo);
}

void	link_philosophers(t_philo *philo, t_philo *philo_next)
{
	philo->next = philo_next;
	philo_next->prev = philo;
	philo->is_sleeping = false;
	philo->is_eating = false;
	philo->is_dead = false;
	philo->is_thinking = false;
}

void	create_simulation(t_setting *data)
{
	t_philo	*cur_philo;
	t_philo	*new_philo;
	int		i;

	data->philos = create_philosopher(data, 0);
	cur_philo = data->philos;
	i = 1;
	while (i < data->number_of_philo)
	{
		new_philo = create_philosopher(data, i);
		link_philosophers(cur_philo, new_philo);
		cur_philo = new_philo;
		i++;
	}
	link_philosophers(cur_philo, data->philos);
}
