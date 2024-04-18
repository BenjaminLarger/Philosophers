/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blarger <blarger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:32:09 by blarger           #+#    #+#             */
/*   Updated: 2024/04/18 15:14:26 by blarger          ###   ########.fr       */
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
# include <pthread.h>
# include <sys/time.h>
# include "libft.h"
# include "message.h"
# include "structures.h"

/* INPUT */
int				set_state_info_to_struct(int argc, char **argv,
					t_setting *data);
t_philo			*create_philos_array(t_setting *data);

/* INIT */

/* SIMULATION */
int				init_simulation(t_setting *data);
int				loop_simulation(t_setting *data);
void			constant_check_table(t_setting *data);
void			break_simulation(t_setting *data, pthread_t *threads);

/* MUTEX */
void			initialize_mutex(t_setting *data);
void			destroy_mutex(t_setting *data);
void			lock_mutex(pthread_mutex_t *mutex);
void			unlock_mutex(pthread_mutex_t *mutex);

/* UTILS */
long long		current_time_stamp_in_ms(void);
bool			philo_must_die(t_philo *philo);
bool			all_philo_have_finished_max_meals(t_setting *data);
int				ft_usleep(useconds_t usec);

/* FORKS */
void			set_forks_to_philo(t_philo *philo);
int				philo_grab_forks(t_philo *philo);
void			philo_drop_forks(t_philo *philo);

/* PRINT */
void			print_death(int philo_i, t_philo *philo);
void			print_state_change(const char *message, int philo_index,
					t_philo *data);

/* ERROR */
int				print_error_and_return(char *str, int to_return);
int				free_print_error(char *str, int to_return, t_setting *data);


#endif