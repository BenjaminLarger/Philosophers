#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void	*forks_routine(void *philos)
{
	struct s_philo	*philos_copy;

	philos_copy = (struct s_philo *)philos;
	pthread_mutex_lock(philos_copy->fork.mutex_fork);
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
	pthread_mutex_unlock(philos_copy->fork.mutex_fork);
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
		data->philos[i].fork.mutex_fork = &mutex;
		if (pthread_create(&thread[i],
				NULL, &forks_routine, &data->philos[i]))
			return (free_data_print_error_and_exit(THREAD_CREATE, EXIT_FAILURE, data));
		i++;
	}
	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (free_data_print_error_and_exit(THREAD_JOIN, EXIT_FAILURE, data));
		i++;
		printf("Fork thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Forks mutex done\n");
}