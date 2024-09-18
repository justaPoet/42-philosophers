/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:37:57 by febouana          #+#    #+#             */
/*   Updated: 2024/09/18 19:03:28 by febouana         ###   ########.fr       */
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
