/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:23:04 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 15:14:55 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	lock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
		return (ft_putstr_fd(MUTEX_LOCK, 2));
}

void	unlock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
		return (ft_putstr_fd(MUTEX_UNLOCK, 2));
}

void	break_simulation(t_setting *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_detach(threads[i]);
		i++;
	}
}

int	print_error_and_return(char *str, int to_return)
{
	ft_putstr_fd(str, 2);
	return (to_return);
}

int	free_print_error(char *str, int to_return, t_setting *data)
{
	free(data);
	ft_putstr_fd(str, 2);
	return (to_return);
}