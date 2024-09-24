/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:37:57 by febouana          #+#    #+#             */
/*   Updated: 2024/09/24 19:23:29 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

data_t *get_data()
{
    static data_t data;
    return (&data);
}

//? Permet de retourner le temps de depart EPOCH.
long long    get_current_time(void)
{
    struct timeval    tv;
    long long        milliseconds;

    if (gettimeofday(&tv, NULL) == -1)
        return (-1);
    milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
    return (milliseconds);
}

void destroy_fork(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_mutex_destroy(&data.philosophers[i].fork_l) != 0)
            return ; //!GESTION ERROR
        i++;
    }   
}

int  check_death(data_t *data, int id)
{ 
    if (data->time_to_die <= (data->philosophers[id].last_meal - data->philosophers[id].last_last_meal))
    {
        if (data->dead == false)
        {    
            data->dead = true;
            data->id_philo_dead = id;
            data->time_death =  get_current_time() - data->start_time;
            unlock_forks(*data, id);
        }
        return (2);
    }
    return (0);
}

int  check_death_solo(data_t *data, int id)
{
    if (data->philosophers[id].left_locked)
        pthread_mutex_unlock(&data->philosophers[id].fork_l);
    usleep(data->time_to_die * 1000);
    data->dead = true;
    data->id_philo_dead = id;
    data->time_death =  get_current_time() - data->start_time;
    return (2);
}

int print_action(data_t data, long long time, char *emoji, char *action, int id)
{
    if (data.dead == true )
        return (2);
    pthread_mutex_lock(&data.print);
    printf("%lld %s (%d) %s", time, emoji, id, action);
    pthread_mutex_unlock(&data.print);
    return (0);
}

void unlock_forks(data_t data, int id) 
{
    if (data.philosophers[id].right_locked)
        pthread_mutex_unlock(data.philosophers[id].fork_r);
    if (data.philosophers[id].left_locked)
        pthread_mutex_unlock(&data.philosophers[id].fork_l);
}
