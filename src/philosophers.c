/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:49:20 by febouana          #+#    #+#             */
/*   Updated: 2024/09/11 17:50:39 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *philosopher_routine()
{
    printf("philo commence a gimgembre\n");
    printf("philo a fini de gimgembre\n");
    return (NULL);
}

void create_philosophers(table_t **list, data_t *data)
{
    int i;

    i = 0;
    while(i <= data->nbr_philos)
        insert_back_dlist(list, i++ + 1);
}

//? - Test with 5 800 200 200, no one should die!
//? ./philo 5 800 200 200
int main(int argc, char **argv)
{ 
    if (argc < 2) //! TEST a changer
        return (1);
    long i;
    data_t *data;
    table_t *list;

    data = malloc(sizeof(data_t));
    list = NULL;
    data->nbr_philos = ft_atol(argv[1]);
    printf("ATOL==%ld\n\n\n", data->nbr_philos);

    create_philosophers(&list, data);

    i = 0;
    while (i < data->nbr_philos)
    {
        if (pthread_create(&list->philosopher, NULL, &philosopher_routine, NULL) != 0)
            return (1);
        printf("==>PHILO(%ld) created\n", list->position_order);
        list = list->next;       
        i++;
    }
    // i = 0;
    // while (i < data->nbr_philos)
    // {
    //     if (pthread_join(list->philosopher, NULL) != 0)
    //         return (1);
    //     printf("main : philo(%ld) joined\n", i + 1);    
    //     list = list->next; 
    //     i++;
    // }
    return (0);
}









