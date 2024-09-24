/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:50:01 by febouana          #+#    #+#             */
/*   Updated: 2024/09/24 19:11:42 by febouana         ###   ########.fr       */
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

//* NETTOYAGE ALGO
//* ==> check si les mutex sont utilises pour checker le status des fork
//* ==> checker comment la mort des philos sont verifies et s'il y a un mutex pour eviter un philosophe de mourrir (triche)

//* cas relou si 1 seul philo (+ revoir les initialisations ??)

typedef struct philo_status
{
	pthread_t			philo;
	int					philo_id;
	int					repeat_meal_philo;
	pthread_mutex_t		fork_l;
	pthread_mutex_t		*fork_r;

    bool_t 				left_locked;
    bool_t 				right_locked;			
	
	long long			last_meal;
	long long			last_last_meal;

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

	bool_t			dead; //! si un philo mort
	int 			id_philo_dead;
	long long 		time_death;	

	pthread_mutex_t print;

	
}					data_t;

//+ philosophers.c
void join_philosophers(data_t data);
//
//

//+ philosophers_routine.c
int 				verif_eating(data_t *data, long obj_usleep, int id);
int 				verif_sleeping(data_t *data, long obj_usleep, int id);
int 				complet_routine(data_t *data, int id);
void				*philosopher_routine(void *index);

//+ philosophers_utils.c
data_t				*get_data(void);
void				destroy_fork(data_t data);

int  				check_death(data_t *data, int id);
int  				check_death_solo(data_t *data, int id);
long long			get_current_time(void);

int print_action(data_t data, long long time, char *emoji, char *action, int id);

//+ gestion_errors.c
void				error(void);
void				error_prompt(void);
void				error_forks(data_t *data);
void				good_ending(data_t *data);

//+ libft_utils.c
long				ft_atol(const char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);


data_t 				*get_data_copy();
void 				unlock_forks(data_t data, int id);

#endif
