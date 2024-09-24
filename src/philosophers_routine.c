/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/24 20:01:01 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int verif_routine(data_t *data, int id)
{
    if (data->time_to_eat >= data->time_to_die)
    {   
        if (data->dead == false)
        {    
            data->dead = true;
            data->id_philo_dead = id;
            data->time_death =  get_current_time() - data->start_time;
            unlock_forks(*data, id);
        }
        usleep(data->time_to_die * 1000);
        return (2);
    }       
    return (0);
}

int verif_eating(data_t *data, long t_eat, int id)
{
    if (data->dead == true)
        return (2);
    if (t_eat >= data->time_to_die)
    {   
        if (data->dead == false)
        {    
            data->dead = true;
            data->id_philo_dead = id;
            data->time_death =  get_current_time() - data->start_time;
            unlock_forks(*data, id);
        }
        usleep(data->time_to_die * 1000);
        return (2);
    }    
    print_action(*data, get_current_time() - data->start_time, "🍝" ,"IS EATING\n", id + 1);    
    data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
    data->philosophers[id].last_meal = get_current_time() - data->start_time;
    usleep(t_eat * 1000);
    return (0);
}

int verif_sleeping(data_t *data, long t_sleep, int id)
{
    if (data->dead == true)
        return (2);
    if (t_sleep >= data->time_to_die)
    {
        if (data->dead == false)
        {    
            data->dead = true;
            data->id_philo_dead = id;
            data->time_death =  get_current_time() - data->start_time;
            unlock_forks(*data, id);
        }
        usleep(data->time_to_die * 1000);
        return (2);
    }
    print_action(*data, get_current_time() - data->start_time, "💤" ,"IS SLEEPING\n", id + 1);  
    usleep(t_sleep * 1000);
    return (0);
}

int complet_routine(data_t *data, int id)
{    
    // bool_t left_locked;
    // bool_t right_locked;
    
    while(data->dead == false && (data->philosophers[id].repeat_meal_philo != 0))
    { 
        if (check_death(data, id) == 2)
            return (2);
        if (pthread_mutex_lock(&data->philosophers[id].fork_l) == 0)
            data->philosophers[id].left_locked = true;
        print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);  
        if (data->nbr_philos == 1) //!
            if (check_death_solo(data, id) == 2) //!
                return (2);
        if (pthread_mutex_lock(data->philosophers[id].fork_r) == 0)
            data->philosophers[id].right_locked = true;
        print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);
        verif_eating(data, data->time_to_eat, id);
        pthread_mutex_unlock(&data->philosophers[id].fork_l); 
        data->philosophers[id].left_locked = false;
        pthread_mutex_unlock(data->philosophers[id].fork_r);
        data->philosophers[id].left_locked = false;
        verif_sleeping(data, data->time_to_sleep, id);
        print_action(*data, get_current_time() - data->start_time, "🤔" ,"IS THINKING\n", id + 1);
        data->philosophers[id].repeat_meal_philo--;
    }
    return (0);
}

data_t *get_data_copy()
{
    data_t *data = malloc(sizeof(data_t));
    if (data == NULL)
        return NULL;
    *data = *(get_data());  // Copie les données existantes si nécessaire
    return data;
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










//! =======================================================================

// #include "../includes/philosophers.h"

// int verif_routine(data_t *data, int id)
// {
//     if (data->time_to_eat >= data->time_to_die)
//     {   
//         if (data->dead == false)
//         {    
//             data->dead = true;
//             data->id_philo_dead = id;
//             data->time_death =  get_current_time() - data->start_time;
//             destroy_fork(*data);
//         }
//         usleep(data->time_to_die * 1000);
//         return (2);
//     }       
//     return (0);
// }

// int verif_eating(data_t *data, long t_eat, int id)
// {
//     if (data->dead == true)
//         return (2);
//     if (t_eat >= data->time_to_die)
//     {   
//         if (data->dead == false)
//         {    
//             data->dead = true;
//             data->id_philo_dead = id;
//             data->time_death =  get_current_time() - data->start_time;
//             destroy_fork(*data);
//         }
//         usleep(data->time_to_die * 1000);
//         return (2);
//     }    
//     print_action(*data, get_current_time() - data->start_time, "🍝" ,"IS EATING\n", id + 1);    
//     data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
//     data->philosophers[id].last_meal = get_current_time() - data->start_time;
//     usleep(t_eat * 1000);
//     return (0);
// }

// int verif_sleeping(data_t *data, long t_sleep, int id)
// {
//     if (data->dead == true)
//         return (2);
//     if (t_sleep >= data->time_to_die)
//     {
//         if (data->dead == false)
//         {    
//             data->dead = true;
//             data->id_philo_dead = id;
//             data->time_death =  get_current_time() - data->start_time;
//             destroy_fork(*data);
//         }
//         usleep(data->time_to_die * 1000);
//         return (2);
//     }
//     print_action(*data, get_current_time() - data->start_time, "💤" ,"IS SLEEPING\n", id + 1);  
//     usleep(t_sleep * 1000);
//     return (0);
// }

// int complet_routine(data_t *data, int id)
// {    
//     while(data->dead == false && (data->philosophers[id].repeat_meal_philo != 0))
//     { 
//         if (check_death(data, id) == 2)
//             return (2);
//         pthread_mutex_lock(&data->philosophers[id].fork_l);
//         print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);  
//         if (data->nbr_philos == 1) //!
//             if (check_death_solo(data, id) == 2) //!
//                 return (2);
//         pthread_mutex_lock(data->philosophers[id].fork_r);
//         print_action(*data, get_current_time() - data->start_time, "🍴" ,"HAS TAKEN A FORK\n", id + 1);
//         verif_eating(data, data->time_to_eat, id);;
//         pthread_mutex_unlock(&data->philosophers[id].fork_l); 
//         pthread_mutex_unlock(data->philosophers[id].fork_r);
//         verif_sleeping(data, data->time_to_sleep, id);
//         print_action(*data, get_current_time() - data->start_time, "🤔" ,"IS THINKING\n", id + 1);
//         data->philosophers[id].repeat_meal_philo--;
//     }
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
//     {
//         if (verif_routine(data, id) == 2)
//             return (NULL);
//         usleep(data->time_to_eat * 1000);
//     }
//     complet_routine(data, id);
//     return (NULL);
// }
