/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_clean_program.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:28:23 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 18:49:23 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_list(t_setting *data)
{
	int	i;
	t_philo	*cur;

	i = 0;
	while(i < data->number_of_philo)
	{
		cur = data->philos;
		data->philos = data->philos->next;
		free(cur);
		i++;
	}
}

void	free_list_until_index(t_setting *data, int index)
{
	int	i;
	t_philo	*cur;

	i = 0;
	while(i < index)
	{
		cur = data->philos;
		data->philos = data->philos->next;
		free(cur);
		i++;
	}
}
