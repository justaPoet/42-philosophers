/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:37:57 by febouana          #+#    #+#             */
/*   Updated: 2024/09/22 23:33:17 by febouana         ###   ########.fr       */
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

int ft_usleep(data_t *data, long long obj_usleep)
{
    if ((obj_usleep) >= (data->time_to_die))
    {
        usleep(data->time_to_die * 1000);
        return (2);
    }
    usleep(obj_usleep * 1000);
    return (0);
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
