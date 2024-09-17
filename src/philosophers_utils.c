/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:37:57 by febouana          #+#    #+#             */
/*   Updated: 2024/09/17 20:25:54 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

data_t *get_data()
{
    static data_t data;
    return (&data);
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
