/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:37:11 by blarger           #+#    #+#             */
/*   Updated: 2024/04/13 17:13:42 by blarger          ###   ########.fr       */
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
		//printf("philo %d", cur.index);
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

/* void	print_list2(t_philo *philos)
{
	int		i;
	t_philo	*cur;

	cur = philos;
	i = 0;
	while (i < 5)
	{
		printf("i = %d\n", i);
		printf("philo %d", philos[i].index);
		if (philos->is_eating == true)
			printf(" is_eating");
		printf("\n");
		philos = philos->next;
		i++;
	}
	while (i > 0)
	{
		philos = philos->prev;
		i--;
	}
}  */

void	print_array(t_setting *data)
{
	int	i;

	printf("----------------------------------------\n");
	i = 0;
	while (i < data->number_of_philo - 1)
	{
		printf("philo %d\t", data->philos[i].index);
		if (data->philos[i].fork.is_available == false && data->philos[i + 1].fork.is_available == false)
			printf("\nPhilo can eat\n");
		printf("\tnext = %d", data->philos[i].next->index);
		printf("\tprev = %d\n", data->philos[i].prev->index);
		i++;
	}	
}
