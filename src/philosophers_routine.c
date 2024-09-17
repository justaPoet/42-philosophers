/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/17 21:18:25 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// 1 🍴 takes forks
// 2 🍝 is_eating
// 3 😴 is_sleeping
// 4 🤔 is_thinking (apres sleep oeoe)

void eating(data_t *data, int id)
{
    if (id % 2 == 0)
        usleep(1);
    data->philosophers[id - 1].is_taking_forks = true;
    data->philosophers[id - 1].is_eating = true;
    pthread_mutex_lock(&data->philosophers[id - 1].fork_l);
    printf("| 🍴 (%d) took the left fork       |\n", id);
    pthread_mutex_lock(data->philosophers[id - 1].fork_r);
    printf("| 🍴 (%d) took the right fork      |\n", id);
    printf("| 🍝 (%d) is eating                |\n", id);
    pthread_mutex_unlock(&data->philosophers[id - 1].fork_l); 
    printf("| 🍴 (%d) put down the left fork   |\n", id);
    pthread_mutex_unlock(data->philosophers[id - 1].fork_r);
    printf("| 🍴 (%d) put down the right fork  |\n", id);
    data->philosophers[id - 1].is_taking_forks = false;
    data->philosophers[id - 1].is_eating = false;
}

//? Creer routine : manger / dormir / penser
//! + cas a part si qu'un seul philo (probleme fourchette)
void	*philosopher_routine(void *index)
{
	//! cas si qu'1 seul philo // if (data->nbr_philos == 1) ou if (fork_l == fork_r)

    data_t *data;
    data = get_data();
    int id = *(int*)index;

    // printf("ID==%d\n", id);
    // printf("ID==%d\n", data->philosophers[id - 1].philo_id);

    
    while (data->repeat_meal > 0)
    {
        //take_forks(data, id);
        eating(data, id);
        // sleeping(data);
        // thinking(data);
        data->repeat_meal--;
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
