/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:49:20 by febouana          #+#    #+#             */
/*   Updated: 2024/09/12 20:14:35 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


//! +++ creer routine manger / dormir / penser +++
void *philosopher_routine()
{
    printf("philo commence a gimgembre\n");
    printf("philo a fini de gimgembre\n");

    return (NULL);
}

void create_philosophers(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_create(&data.philosophers[i].philo, NULL, &philosopher_routine, NULL) != 0)
            return ;  //! GESTION ERROR   
        data.philosophers[i].philo_id = i + 1;
        printf("ID==%ld\n", data.philosophers[i].philo_id);
        printf("==>PHILO(%ld) created\n", data.philosophers[i].philo_id);
        i++;
    }   
}

void join_philosophers(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_join(data.philosophers[i].philo, NULL) != 0)
            return ;   //! GESTION ERROR   
        i++;
    } 
}

//? - Test with 5 800 200 200, no one should die!
//? ./philo 5 800 200 200
//? 5 => nbr_philos
//? 800 => time_to_die
//? 200 => time_to_eat
//? 200 => time_to_sleep
//+ l'importance de join tot ??????
int main(int argc, char **argv)
{ 
    data_t *data;
    
    if (argc < 2) //! cas avec argv[1] == 0
        return (write(1, "\n", 1));

    data = malloc(sizeof(data_t));
    if (!data)
        return (write(1, "\n", 1));


    data->nbr_philos = ft_atol(argv[1]); //OKOK
    if (data->nbr_philos > 200)
        return (write(1, "\n", 1));
    data->time_to_die = ft_atol(argv[2]); //OKOK
    data->time_to_eat = ft_atol(argv[3]); //OKOK
    data->time_to_sleep = ft_atol(argv[4]); //OKOK

    data->philosophers = malloc(data->nbr_philos * sizeof(philo_status_t));
    if (!data->philosophers)
        return (write(1, "\n", 1));

    create_philosophers(*data);
    join_philosophers(*data);
    
    free(data->philosophers);
    return (0);
}
