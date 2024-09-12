/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:50:01 by febouana          #+#    #+#             */
/*   Updated: 2024/09/12 19:08:23 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h> //ABSOLUMENT TOUT 
# include <stdio.h>  //printf
# include <stdlib.h> //malloc+free
# include <string.h> //memset
# include <unistd.h> //usleep

typedef enum bool
{
	false,
	true
}			bool_t;

typedef struct philo_status
{
	pthread_t		        	philo;
	long 						philo_id;

	// pthread_mutex_t				spoon_l; //!
	// pthread_mutex_t				spoon_r; //!
				
	bool_t						is_eating; //!
	bool_t						is_dead; //!
}								philo_status_t;

typedef struct data
{
	philo_status_t 				*philosophers;
	long						nbr_philos;
	long 						time_to_die;
	long 						time_to_eat;
	long 						time_to_sleep;
}					       		data_t;

//+ philosophers.c
//
//
//

//+ philosophers_utils.c
long	ft_atol(const char *str);


#endif