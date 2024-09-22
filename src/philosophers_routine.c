/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/23 00:16:22 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// 1 🍴 takes forks
// 2 🍝 is_eating
// 3 💤 is_sleeping
// 4 🤔 is_thinking (apres sleep oeoe)
// 5 ☠️  IS DEAD

int  check_death(data_t *data, int id)
{
    //!appel fn verif pour chaque philo si un philo est mort
    
    if (data->nbr_philos == 1) 
        usleep(data->time_to_die * 1000);
    if ((data->nbr_philos == 1) || (data->time_to_die <= (data->philosophers[id].last_meal - data->philosophers[id].last_last_meal)))
    {
        join_philosophers(*data);
        destroy_fork(*data);
        printf("%lld ☠️  (%d) IS DEAD ====================================================\n", get_current_time() - data->start_time, id + 1);
        return (2);
    }
    return (0);
}

int philo_is_eating(data_t *data, int id)
{      
    pthread_mutex_lock(&data->philosophers[id].fork_l);
    printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
    if (check_death(data, id) == 2)
        return (2);
    pthread_mutex_lock(data->philosophers[id].fork_r);
    printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
    printf("%lld 🍝 (%d) is eating\n", get_current_time() - data->start_time, id + 1);
    if (ft_usleep(data, data->time_to_eat * 1000))
        check_death(data, id);
    data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
    data->philosophers[id].last_meal = get_current_time() - data->start_time;
    pthread_mutex_unlock(&data->philosophers[id].fork_l); 
    pthread_mutex_unlock(data->philosophers[id].fork_r);
    return (0);
}

void philo_is_sleeping_thinking(data_t *data, int id)
{
    printf("%lld 💤 (%d) is sleeping\n", get_current_time() - data->start_time, id + 1);
    if (ft_usleep(data, data->time_to_sleep) == 2)
        check_death(data, id);
    printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
}

void	*philosopher_routine(void *index)
{
    data_t *data;
    data = get_data();
    int id = *(int*)index - 1;

    if (id % 2 != 0)
        usleep(data->time_to_eat * 1000);
    while(data->philosophers[id].repeat_meal_philo != 0)
    {
        if (philo_is_eating(data, id) == 2)
            exit (2); //! sortie propre 
        data->philosophers[id].repeat_meal_philo--;
        philo_is_sleeping_thinking(data, id);	
    }
    return (NULL);
}
























// printf("(%d)>>>lastmeal==%lld | ", id + 1, data->philosophers[id].last_meal); 
// printf("(%d)>>>lastlastmeal==%lld\n", id + 1, data->philosophers[id].last_last_meal);  
// printf("(%d)>>>LASTMEAL-LASTLASTMEAL==%lld\n\n", id + 1, data->philosophers[id].last_meal - data->philosophers[id].last_last_meal);   
    

//? VERSION AVANT SPLIT
// int complet_routine(data_t *data, int id)
// {     
//     if (id % 2 != 0)
//         usleep(data->time_to_eat * 1000);
//     while(data->philosophers[id].repeat_meal_philo != 0)
//     {    
//         //verif pour chaque philo qui check si un philo est mort
//         if (data->time_to_die <= (data->philosophers[id].last_meal - data->philosophers[id].last_last_meal))
//         {
//             join_philosophers(*data);
//             destroy_fork(*data);
//             printf("%lld ☠️  (%d) IS DEAD\n", get_current_time() - data->start_time, id + 1);
//             exit (2);
//         }
//     //? DEBUT        
//         data->philosophers[id].will_eat = true;    
//     //? is_taking_fork_l (la sienne)
//         data->philosophers[id].is_taking_fork_l = true;
//         pthread_mutex_lock(&data->philosophers[id].fork_l);
//         printf("%lld 🍴 (%d) took the left fork\n", get_current_time() - data->start_time, id + 1);
                
//     //? is_taking_fork_r (celle du philo de droite)
//         data->philosophers[id].is_taking_fork_r = true;
//         pthread_mutex_lock(data->philosophers[id].fork_r);
//         printf("%lld 🍴 (%d) took the right fork\n", get_current_time() - data->start_time, id + 1);
            
//     //? is_eating
//         printf("%lld 🍝 (%d) is eating\n", get_current_time() - data->start_time, id + 1);
//         usleep(data->time_to_eat * 1000);
//         data->philosophers[id].repeat_meal_philo--;
        
//         data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
//         data->philosophers[id].last_meal = get_current_time() - data->start_time; //+ marque le temps qui s'est ecoule depuis debut du prog ou philo a manger pour la dernier foi

//     //? put down fork_l and fork_r
//         pthread_mutex_unlock(&data->philosophers[id].fork_l); 
//         data->philosophers[id].is_taking_fork_l = false;
//         pthread_mutex_unlock(data->philosophers[id].fork_r);
//         data->philosophers[id].is_taking_fork_r = false;
            
//     //? FIN
//         data->philosophers[id].will_eat = false;
//         printf("%lld 💤 (%d) is sleeping\n", get_current_time() - data->start_time, id + 1);
//         usleep(data->time_to_sleep * 1000); //OKOK
//         printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
//     }
// }

// //? Creer routine : manger / dormir / penser
// void	*philosopher_routine(void *index)
// {
// 	//! cas si qu'1 seul philo // if (data->nbr_philos == 1) ou if (fork_l == fork_r)

//     data_t *data;
//     data = get_data();
//     int id = *(int*)index - 1; //pour revenir a un index propre
    

//     if (complet_routine(data, id) == 2)
//         return (2);   
// 	return (NULL);
// }