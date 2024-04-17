/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_check_table.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:27:23 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 12:04:12 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	break_simulation(t_setting *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

void	constant_check_table(t_setting *data, pthread_t *threads)
{
	int		i;
	bool	to_break;

	to_break = false;
	while (to_break == false)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			if (all_philo_have_finished_max_meals(&data->philos[i]) == true)
			{
				to_break = true;
				lock_mutex(&data->mutex_exit);
				data->must_exit = true;
				unlock_mutex(&data->mutex_exit);
				break_simulation(data, threads);
				break ;
			}
			if (philo_must_die(&data->philos[i]) == true)
			{
				to_break = true;
				break_simulation(data, threads);
				break ;
			}
			i++;
		}
	}
	printf("constant check done\n");
}
