/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/10/04 21:54:10 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool_t stop_signal(data_t *data, bool_t dead)
{
    pthread_mutex_lock(&data->m_stop);
    if (data->stop == true)
    {
        dead = true;
        pthread_mutex_unlock(&data->m_stop);
        return (true);
    }
    pthread_mutex_unlock(&data->m_stop);
    return (false);
}

void will_die(data_t *data, int id, bool_t dead)
{
    pthread_mutex_lock(&data->m_stop);
    if (data->stop == false)
    {
        data->stop = true;
        unlock_forks(data, id);
        usleep(data->time_to_die * 1000);   
        print_all_action(data, 4, id, get_current_time() - data->start_time, dead); //!
        data->philosophers[id].is_dead = true;
    }
    pthread_mutex_unlock(&data->m_stop);
}

int verif_sleeping_thinking(data_t *data, long time_to_sleep, int id, bool_t dead)
{    
    if (time_to_sleep >= data->time_to_die)
    {
        will_die(data, id, dead);
        return (2);
    }
    if (stop_signal(data, data->philosophers[id].is_dead))
        return (2);
    print_all_action(data, 2, id, get_current_time() - data->start_time, dead); //!
    usleep(time_to_sleep * 1000);
    print_all_action(data, 3, id, get_current_time() - data->start_time, data->philosophers[id].is_dead); //? safe
    return (0);
}

int verif_eating(data_t *data, long time_to_eat, int id, bool_t dead)
{    
    //printf("$$$$$$$<%d> last_meal - last_last_meal==%lld\n", id + 1, (get_current_time() - data->start_time) - data->philosophers[id].last_meal);
    if (data->time_to_die < ((get_current_time() - data->start_time) - data->philosophers[id].last_meal))
    {
        will_die(data, id, dead);
        return (2);
    }
    if (stop_signal(data, data->philosophers[id].is_dead))
        return (2);
    data->philosophers[id].last_meal =  get_current_time() - data->start_time;  //?safe
    usleep(time_to_eat * 1000);
    print_all_action(data, 1, id, get_current_time() - data->start_time, dead); //!
    unlock_forks(data, id);
    return (0);
}

int take_forks(data_t *data, int id, bool_t dead)
{
    lock_first_fork(data, id, dead);
    lock_second_fork(data, id, dead);
    return (0);
}

// $> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([number_of_times_each_philosopher_must_eat])

int complet_routine(data_t *data, int id)
{
    if (data->time_to_die <= (data->time_to_eat))
    {
        will_die(data, id, data->philosophers[id].is_dead);
        return (2);
    }
    else 
    {
        if (id % 2 != 0)
            usleep(data->time_to_eat * 1000);
    }
    while(data->philosophers[id].repeat_meal_philo != 0)
    {   
        if (data->philosophers[id].is_dead || stop_signal(data, data->philosophers[id].is_dead))
            break ;
        take_forks(data, id, data->philosophers[id].is_dead);
        verif_eating(data, data->time_to_eat, id, data->philosophers[id].is_dead);
        verif_sleeping_thinking(data, data->time_to_sleep, id, data->philosophers[id].is_dead);
        data->philosophers[id].repeat_meal_philo--; //?safe
    }
    unlock_forks(data, id);
    return (0);
}

int routine_solo(data_t *data, int id)
{
    lock_first_fork(data, id, data->philosophers[id].is_dead);
    unlock_forks(data, id);
    will_die(data, id, data->philosophers[id].is_dead);
    return (0);
}


void	*philosopher_routine(void *philo)
{
    data_idx_t data_index = *(data_idx_t *)philo;
    free(philo);
    
    if (data_index.data->nbr_philos == 1)
        routine_solo(data_index.data, data_index.idx);
    else
        complet_routine(data_index.data, data_index.idx);
    return (NULL);
}


//1/ reimplanter le systeme de mort             //*OKKKKKKKK
// -meurt de faim cas normal                    //*OKOK
// -meurt car diff de temps pour dormir         //*OKOK
// -meurt car diff de temps pour manger         //*OKOK
//2/ reimplanter cas avec 1 seul philo          //*OKKKKKKKK

//+ pour micro optimiser le calcul final : mettre un tri baleze que pour le premier passage, pas besoin pour ceux d'apres et trop gourmand
