/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:50:01 by febouana          #+#    #+#             */
/*   Updated: 2024/09/19 19:06:25 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>  //ABSOLUMENT TOUT'
# include <stdio.h>    //printf
# include <stdlib.h>   //malloc+free
# include <string.h>   //memset
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //usleep

typedef enum bool
{
	false,
	true
}					bool_t;

typedef struct philo_status
{
	pthread_t		philo;
	int				philo_id;
	int				repeat_meal_philo;

	pthread_mutex_t	fork_l;
	pthread_mutex_t	*fork_r;

	bool_t			is_taking_fork_l;
	bool_t			is_taking_fork_r;

	bool_t 			will_eat;  //!
	bool_t 			is_eating; //!

	bool_t 			is_thinking;  //!
	bool_t 			is_till_dead; //!
	bool_t 			is_dead;      //!
	long long		last_meal;
}					philo_status_t;

typedef struct data
{
	philo_status_t	*philosophers;
	long			nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			repeat_meal;
	long long		start_time;
}					data_t;

//+ philosophers.c
//
//
//

//+ philosophers_routine.c
void				*philosopher_routine(void *index_philo);

//+ philosophers_utils.c
data_t				*get_data(void);
void				destroy_fork(data_t data);
long long			get_current_time(void);

//+ gestion_errors.c
void				error(void);
void				error_prompt(void);
void				error_forks(data_t *data);
void				good_ending(data_t *data);

//+ libft_utils.c
long				ft_atol(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);

#endif