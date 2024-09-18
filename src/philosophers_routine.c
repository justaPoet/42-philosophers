/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/18 21:05:54 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// 1 🍴 takes forks
// 2 🍝 is_eating
// 3 😴 is_sleeping
// 4 🤔 is_thinking (apres sleep oeoe)

void complet_routine(data_t *data, int id)
{
    if (id % 2 != 0) // OKOK
		usleep(data->time_to_eat * 1000); //OKOK
	if (id == 0)
		while (data->philosophers[data->nbr_philos].will_eat == true || data->philosophers[1].will_eat == true)
			usleep(1);		
	if (id == data->nbr_philos)
		while (data->philosophers[data->nbr_philos - 1].will_eat == true || data->philosophers[0].will_eat == true)
			usleep(1);
	else
    	while (data->philosophers[id - 1].will_eat == true || data->philosophers[id + 1].will_eat == true)
        	usleep(1);
			
    if (data->philosophers[id - 1].is_taking_fork_r == false && data->philosophers[id + 1].is_taking_fork_l == false) 
    {
        data->philosophers[id].will_eat = true;
        
    // is_taking_fork_l (la sienne)
        data->philosophers[id].is_taking_fork_l = true;
        pthread_mutex_lock(&data->philosophers[id].fork_l);
        printf("🍴 (%d) took the left fork\n", id + 1);

    // is_taking_fork_r (celle du philo de droite)
        data->philosophers[id].is_taking_fork_r = true;
        pthread_mutex_lock(data->philosophers[id].fork_r);
        printf("🍴 (%d) took the right fork\n", id + 1);
        
    // is_eating
        printf("🍝 (%d) is eating\n", id + 1);
        usleep(data->time_to_eat * 1000);
		data->repeat_meal--;
        if (data->philosophers[id].is_till_dead == true)
            data->philosophers[id].is_till_dead = false;

    // put down fork_l
        pthread_mutex_unlock(&data->philosophers[id].fork_l); 
        data->philosophers[id].is_taking_fork_l = false;
        //printf("🍴 (%d) put down the left fork\n", id + 1);

    // put down fork_r
        pthread_mutex_unlock(data->philosophers[id].fork_r);
        data->philosophers[id].is_taking_fork_r = false;
        //printf("🍴 (%d) put down the right fork\n", id + 1);

        data->philosophers[id].will_eat = false;
        //! reset last_meal

		printf("😴 (%d) is sleeping\n", id + 1);
		usleep(data->time_to_sleep * 1000); //OKOK
		printf("🤔 (%d) is thinking\n", id + 1);
    }
}

//? Creer routine : manger / dormir / penser
//! + cas a part si qu'un seul philo (probleme fourchette)
void	*philosopher_routine(void *index)
{
	//! cas si qu'1 seul philo // if (data->nbr_philos == 1) ou if (fork_l == fork_r)

    data_t *data;
    data = get_data();
    int id = *(int*)index - 1; //pour revenir a un index propre

    // printf("ID==%d\n", id);
    // printf("ID==%d\n", data->philosophers[id - 1].philo_id);

    
    while (data->repeat_meal > 0)
    {
        complet_routine(data, id);
            // die(data, id)
        // sleeping(data, id);
        // thinking(data, id);
            
    }
	return (NULL);
}






    

// le premier prio a manger est le philo 1
// comprendre fn temporalite

// void *philosopher_routine(data_t *data)
// {
//     // if (data->nbr_philos == 1)
//     // {
//     //     ft_putstr_fd("a philo is dead.\n", 2);
//     //     return (NULL);
//     // }
//     printf("philo commence a gimgembre\n");
//     printf("philo a fini de gimgembre\n");

//     return (NULL);
// }
