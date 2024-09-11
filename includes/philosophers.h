/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:50:01 by febouana          #+#    #+#             */
/*   Updated: 2024/09/11 15:43:44 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h> //ABSOLUMENT TOUT 
# include <stdio.h>  //printf
# include <stdlib.h> //malloc+free
# include <string.h> //memset
# include <unistd.h> //usleep

typedef struct philo_data
{
	long						nbr_philos;
	long 						time_to_die;
	long 						time_to_eat;
	long 						time_to_sleep;
}					        data_t;

typedef struct philo_table
{
	long 						position_order;
	pthread_t		        	philosopher;
	pthread_mutex_t	        	spoon;
	// pthread_mutex_t	        	eat;
	// pthread_mutex_t	        	sleep;
	// pthread_mutex_t	        	think;
	struct philo_table	        *next;
	struct philo_table	        *back;
}					        table_t;


//+ philosophers.c
//
//
//

//+ philosophers_utils.c
long	ft_atol(const char *str);


//+ chained_list_utils.c
void print_dlist(table_t **stack);
table_t	*find_last_node(table_t *philo);
void	insert_back_dlist(table_t **list, int nbr);


#endif