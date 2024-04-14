/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:23:04 by blarger           #+#    #+#             */
/*   Updated: 2024/04/14 19:00:50 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philos_ready_to_state(t_setting *data, char *state)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->number_of_philo)
	{
		if (!(ft_strcmp(state, EATS)))
			count++;
		else if (!(ft_strcmp(state, SLEEP))
			&& data->philos[i].can_eat == true)
			count++;
		else if (!(ft_strcmp(state, THINKS))
			&& data->philos[i].can_think == true)
			count++;
		else if (!(ft_strcmp(state, TAKES_FORK))
			&& data->philos[i].can_sleep == true)
			count++;
		i++;
	}
	return (count);
}

bool	philo_must_die(t_philo *philo)
{
	if (philo->last_meal - current_time_stamp_in_ms() <= 0)
	{
		printf("mutex %p locked\n", (void*)&philo->mutex_death);
		if (pthread_mutex_lock(philo->mutex_death) != 0)
			return (FAILURE);//Handle failure
		print_state_actualization(DIES, philo->index, philo);
		//exit(EXIT_SUCCESS);
		return (true);
	}
	return (false);
}

/* pthread_t	*alloc_thread(t_setting *data, char *condition)
{
	int				i;
	int				count;
	pthread_t		*thread;

	i = 0;
	count = 0;
	while (i < data->number_of_philo)
	{
		if (!(ft_strcmp(condition, EATS))
			&& data->philos[i].can_eat == true)
			count++;
		else if (!(ft_strcmp(condition, SLEEP))
			&& data->philos[i].can_sleep == true)
			count++;
		else if (!(ft_strcmp(condition, THINKS))
			&& data->philos[i].can_think == true)
			count++;
		else if (!(ft_strcmp(condition, TAKES_FORK))) //not sure of this one
			count++;
		i++;
	}
	thread = malloc(sizeof(pthread_t) * count);
	if (!thread)
		return (free_data_print_error_and_exit(MALLOC, EXIT_FAILURE, data), NULL);
	printf("%d threads created\n", count);
	return (thread);
} */
