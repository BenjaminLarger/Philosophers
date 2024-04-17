/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:32:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/17 12:02:33 by blarger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <unistd.h>
# include <strings.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
#include <pthread.h>
#include <sys/time.h>
# include "libft.h"
# include "errors.h"
# include "structures.h"

/* INPUT */
int				set_state_info_to_struct(int argc, char **argv, t_setting *data);
t_philo			*create_philos_array(t_setting *data);

/* INIT */
int				init_simulation(t_setting *data);

/* SIMULATION */
void			print_state_change(const char *message, int philo_index,
					t_philo *data, bool check_table);
void			print_state_change_for_routine(const char *msg, int philo_i,
					t_philo *philo, bool check_table);
long long		current_time_stamp_in_ms();
void			loop_simulation(t_setting *data);
int				philo_grab_forks(t_philo *philo);
void			philo_drop_forks(t_philo *philo);
bool			philo_must_die(t_philo *philo);
void			constant_check_table(t_setting *data, pthread_t *threads);

/* MUTEX */
void			initialize_mutex(t_setting *data);
void			destroy_mutex(t_setting *data);


/* UTILS */
int				philos_ready_to_state(t_setting *data, char *condition);
bool			check_if_a_philo_must_exit(t_philo *philo);
void			lock_mutex(pthread_mutex_t *mutex);
void			unlock_mutex(pthread_mutex_t *mutex);
bool			update_if_philo_has_reached_max_meals(t_philo *philo);
bool			all_philo_have_finished_max_meals(t_philo *philo);
bool			philo_can_exit(t_philo *philo);




/* ERROR */
int				print_error_and_return(char *str, int to_return);
void			print_error_and_exit(char *error_message, int status);

/* CLEANING */
void			free_list(t_setting *data);
void			free_list_until_index(t_setting *data, int index);
void			free_data_print_error_and_exit(char *error_message, int status,
					t_setting *data);

/* DEV */
void			print_array(t_setting *data);
void			print_list(t_setting *data);


#endif