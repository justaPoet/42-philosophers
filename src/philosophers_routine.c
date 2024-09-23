/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/23 19:49:31 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int verif_eating(data_t *data, long obj_usleep, int id)
{
    if (obj_usleep >= data->time_to_die)
    {
        destroy_fork(*data);
        //join_philosophers(*data);
    //print_action(*data, get_current_time() - data->start_time, "☠️" ,"IS DEAD DE FOU MALADE\n", id + 1);
    printf("%lld ☠️  (%d) IS DEAD (too long time to eat 🍝)\n", get_current_time() - data->start_time, id + 1); 
        usleep(data->time_to_die * 1000);
        return (2);
    }    
print_action(*data, get_current_time() - data->start_time, "🍝" ,"IS EATING\n", id + 1);    
// printf("%lld 🍝 (%d) is eating\n", get_current_time() - data->start_time, id + 1);
    data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
    data->philosophers[id].last_meal = get_current_time() - data->start_time;
    usleep(obj_usleep * 1000);
    return (0);
}

int verif_sleeping(data_t *data, long obj_usleep, int id)
{

    if (obj_usleep >= data->time_to_die)
    {
        destroy_fork(*data);
        //join_philosophers(*data);
        usleep(data->time_to_die * 1000);
        printf("%lld ☠️  (%d) IS DEAD (too long time to sleep 💤)\n", get_current_time() - data->start_time, id + 1);
        return (2);
    }
print_action(*data, get_current_time() - data->start_time, "💤" ,"IS SLEEPING\n", id + 1);  
// printf("%lld 💤 (%d) is sleeping\n", get_current_time() - data->start_time, id + 1);
    usleep(obj_usleep * 1000);
    return (0);
}

int complet_routine(data_t *data, int id)
{    
    while(data->dead != true && (data->philosophers[id].repeat_meal_philo != 0))
    { 
        if (check_death(data, id) == 2)
            return (2);
        pthread_mutex_lock(&data->philosophers[id].fork_l);

    print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);       
    //printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
        if (data->nbr_philos == 1)
            if (check_death_solo(data, id) == 2)
                return (2);
        pthread_mutex_lock(data->philosophers[id].fork_r);
    print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);       
    //printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
        if (verif_eating(data, data->time_to_eat, id) == 2)
            return (2);
        pthread_mutex_unlock(&data->philosophers[id].fork_l); 
        pthread_mutex_unlock(data->philosophers[id].fork_r);
        if (verif_sleeping(data, data->time_to_sleep, id) == 2)
            return (2);

    print_action(*data, get_current_time() - data->start_time, "🤔" ,"IS THINKING\n", id + 1);       
    // printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
        data->philosophers[id].repeat_meal_philo--;
    }
    return (0);
}


void	*philosopher_routine(void *index)
{
    data_t *data;
    int id;
    data = get_data();
    id = *(int*)index - 1;

    data->dead = false;

    if (id % 2 != 0)
        usleep(data->time_to_eat * 1000);
    complet_routine(data, id);
    exit(2);
    return (NULL);
}

















//!
// int complet_routine(data_t *data, int id)
// {     
//     if (check_death(data, id) == 2)
//         return (2);
//     pthread_mutex_lock(&data->philosophers[id].fork_l);
//     printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
//     if (data->nbr_philos == 1)
//         if (check_death_solo(data, id) == 2)
//             return (2);
//     pthread_mutex_lock(data->philosophers[id].fork_r);
//     printf("%lld 🍴 (%d) has taken a fork\n", get_current_time() - data->start_time, id + 1);
//     if (verif_eating(data, data->time_to_eat, id) == 2)
//         return (2);
//     // data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
//     // data->philosophers[id].last_meal = get_current_time() - data->start_time;
//     pthread_mutex_unlock(&data->philosophers[id].fork_l); 
//     pthread_mutex_unlock(data->philosophers[id].fork_r);
//     if (verif_sleeping(data, data->time_to_sleep, id) == 2)
//         return (2);
//     printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
//     return (0);
// }


// void	*philosopher_routine(void *index)
// {
//     data_t *data;
//     int id;
//     data = get_data();
//     id = *(int*)index - 1;

//     data->dead = false;

//     if (id % 2 != 0)
//         usleep(data->time_to_eat * 1000);
//     while(data->dead != true && (data->philosophers[id].repeat_meal_philo != 0))
//     {
//         if (complet_routine(data, id) == 2)
//         {
//             printf("\n\nSORTIE PROPRE YOUHOUUUU 🍝🍝🍝🍝🍝🍝🍝🍝🍝\n\n");
//             return (NULL);
//         }
//         data->philosophers[id].repeat_meal_philo--;
//     }
//     return (NULL);
// }
//!




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