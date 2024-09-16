/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:37:57 by febouana          #+#    #+#             */
/*   Updated: 2024/09/16 19:25:50 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void destroy_fork(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_mutex_destroy(&data.philosophers[i].fork_l) == 0)
            printf("== ==> MUTEX DESTOYED (%d)\n", i + 1); //!GESTION ERROR
        i++;
    }   
}
