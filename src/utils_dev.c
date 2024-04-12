/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:11 by blarger           #+#    #+#             */
/*   Updated: 2024/04/12 09:30:00 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_list(t_setting *data)
{
	int		i;
	t_philo	*cur;

	cur = data->philos;
	i = 0;
	printf("---------------------------\n");
	printf("number of philo = %d\ntime before dying = %d\ntime to eat = %d\ntime to sleep = %d\n", data->number_of_philo, data->time_to_die, data->time_to_eat, data->time_to_sleep);
	if (data->max_time_to_eat_set == true)
		printf("max time to eat = %d\n\n", data->max_time_to_eat);
	else
		printf("No maximum time to eat set\n\n");
	while (i < data->number_of_philo)
	{
		printf("philo %d", i);
		if (data->philos->is_eating == true)
			printf(" is_eating");
		printf("\n");
		data->philos = data->philos->next;
		i++;
	}
	while (i > 0)
	{
		data->philos = data->philos->prev;
		i--;
	}
}
