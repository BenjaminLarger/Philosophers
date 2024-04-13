/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:12:12 by blarger           #+#    #+#             */
/*   Updated: 2024/04/13 19:11:58 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	*forks_routine(void *philos)
{
	struct s_philo	*philos_copy;

	philos_copy = (struct s_philo *)philos;
	pthread_mutex_lock(philos_copy->fork.mutex_ptr);
	printf("fork routine for philo %d\n", philos_copy->index);
	if (philos_copy->next->fork.is_available == true)
		printf("\033[0;32m\tnext fork is available for philo %d\n\033[0m", philos_copy->next->index);
	else
		printf("\033[0;31m\tnext fork is not available for philo %d\n\033[0m", philos_copy->next->index);
	if (philos_copy->fork.is_available == true)
		printf("\033[0;32m\tcur fork is available for philo %d\n\033[0m", philos_copy->index);
	else
		printf("\033[0;31m\tcur fork is not available for philo %d\n\033[0m", philos_copy->index);
	if (philos_copy->next->fork.is_available == true
		&& philos_copy->fork.is_available == true)
	{
		printf("\033[0;32m\tTwo forks are available for the philo %d\n\033[0m", philos_copy->index);
		philos_copy->next->fork.is_available = false;
		philos_copy->fork.is_available = false;
	}
	else
		printf("\033[0;31m\tphilo %d does not take forks\n\033[0m", philos_copy->index);
	pthread_mutex_unlock(philos_copy->fork.mutex_ptr);
	return (NULL);
}

void	philo_catch_forks(t_setting	*data)
{
	int				i;
	pthread_t		thread[8];
	pthread_mutex_t mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < data->number_of_philo)
	{
		data->philos[i].fork.mutex_ptr = &mutex;
		if (pthread_create(&thread[i],
				NULL, &forks_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD, EXIT_FAILURE, data));
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
	pthread_mutex_destroy(&mutex);
	printf("Forks mutex done\n");
}

static void	set_forks_to_philo(t_setting *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo
		&& data->philos[i].next->index != 0)
	{
		if (data->philos[i].index % 2 == 0)
		{
			data->philos[i].next->fork.is_available = false;
			print_state_actualization(TAKES_FORK, i, &data->philos[i]);
			data->philos[i].fork.is_available = false;
			print_state_actualization(TAKES_FORK, i, &data->philos[i]);
			print_state_actualization(EATS, i, &data->philos[i]);
		}
		else
			print_state_actualization(SLEAPS, i, &data->philos[i]);
		i++;
	}
}

int	init_simulation(t_setting *data)
{
	set_forks_to_philo(data);
	while (a_philo_is_dead(data) == false)
	{
		make_philos_eat(data);
	}
	return (SUCCESS);
}
