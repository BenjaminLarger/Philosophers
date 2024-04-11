/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:35:56 by blarger           #+#    #+#             */
/*   Updated: 2024/04/11 17:18:44 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_listed
{
	struct s_listed		*next;
	struct s_listed		*prev;
	int					index;
}					t_listed;

typedef struct s_philo
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_time_to_eat;
	struct s_listed		list_of_philo;
}					t_philo;

#endif