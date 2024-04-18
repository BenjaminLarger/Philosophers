/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essentials_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:44:59 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 12:23:07 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error_and_return(char *str, int to_return)
{
	ft_putstr_fd(str, 2);
	return (to_return);
}

int	free_print_error(char *str, int to_return, t_setting *data)
{
	if (data->philos)
		free(data->philos);
	free(data);
	ft_putstr_fd(str, 2);
	/* free(forks_mutex);
	free(last_meal_mutex);
	free(max_meal_reach); */
	return (to_return);
}

