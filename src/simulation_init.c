/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/12 17:26:05 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*forks_routine(void *philos)
{
	struct s_philo	*philos_copy;

	philos_copy = (struct s_philo *)philos;
	printf("fork routine for philo %d\n", philos_copy->index);
	pthread_mutex_lock(&philos_copy->fork.mutex);
	if (philos_copy->prev->fork.is_available
		&& philos_copy->fork.is_available)
	{
		printf("\033[0;32m\tTwo forks are available for the philo %d\n\033[0m", philos_copy->index);

		philos_copy->next->fork.is_available = false;
		philos_copy->fork.is_available = false;
	}
	else
		printf("\033[0;31m\tphilo %d does not take forks\n\033[0m", philos_copy->index);
	//printf("philo ready to take a fork\n");
	pthread_mutex_unlock(&philos_copy->fork.mutex);
	return (NULL);
}

void	philo_catch_forks(t_setting	*data)
{
	int				i;
	pthread_t		thread[8];

	i = 0;
	pthread_mutex_init(&data->philos[i].fork.mutex, NULL);
	while (i < data->number_of_philo)
	{
		if (pthread_create(&thread[i],
				NULL, &forks_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD, EXIT_FAILURE, data));
		printf("Fork thread %d has started for philos n%d\n", i, data->philos[i].index);
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD, EXIT_FAILURE, data));
		i++;
		printf("Fork thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&data->philos->fork.mutex);
	printf("Forks mutex done\n");
}

int	init_simulation(t_setting *data)
{
	philo_catch_forks(data);
	return (SUCCESS);
}

/* int	init_simulation(t_setting *data)
{
	int		i;
	t_philo	*cur_philo;

	cur_philo = data->philos;
	i = 0;
	while (i < data->number_of_philo)
	{
		if (cur_philo->prev->is_eating == false
			&& cur_philo->next->is_eating == false)
			cur_philo->is_eating = true;
		cur_philo = cur_philo->next;
		i++;
	}
	return (SUCCESS);
} */
