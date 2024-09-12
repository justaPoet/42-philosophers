/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:49:20 by febouana          #+#    #+#             */
/*   Updated: 2024/09/13 00:05:10 by apoet            ###   ########.fr       */
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

void create_philosophers(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_create(&data.philosophers[i].philo, NULL, &philosopher_routine, NULL) != 0)
            return ;  //! GESTION ERROR   
        data.philosophers[i].philo_id = i + 1;
        i++;
    }   
}

void parsing_args(data_t **data, int argc, char **args)
{
    (*data)->nbr_philos = ft_atol(args[1]);
    if ((*data)->nbr_philos > 200)
        return ; //! GESTION ERROR 
    (*data)->time_to_die = ft_atol(args[2]);
    (*data)->time_to_eat = ft_atol(args[3]);
    (*data)->time_to_sleep = ft_atol(args[4]);
    if (argc == 6) //!
        (*data)->repeat_eat = ft_atol(args[5]);
    else
        (*data)->repeat_eat = 1;
}

void create_forks()
{

 

 
 //+ asign_forks() 
}

//? - Test with 5 800 200 200, no one should die!
//? ./philo 5 800 200 200 (7)
//! importance de join tot ??????
//! besoin d'initialiser d'autres elements a 0 ?? (//memset)
int main(int argc, char **argv)
{ 
    data_t *data;
    
    if (argv[1] == 0 || argc > 6 || argc < 5)
        exit(EXIT_FAILURE);
    data = malloc(sizeof(data_t));
    if (!data)
        return (1); //! GESTION ERROR 
        
    parsing_args(&data, argc, argv);
    
    data->philosophers = malloc(data->nbr_philos * sizeof(philo_status_t));
    if (!data->philosophers)
        return (1); //! GESTION ERROR 

    create_forks(); // asign_forks() 
    create_philosophers(*data); // routine philo la


    
    join_philosophers(*data);

    free(data->philosophers);
    free(data);
    return (0);
}

//+ faire fn pour init les mutexs
    //+ faire fn pour destroy les mutexs
//+ faire fn pour attribuer les forks_l et fork_r a chaque philo 

//+ CODER ALGO:
    //+ ==> routine precise phil (manger, dormir, penser)
        //+ // systeme d'etat "is_eating" + "is_dead" (+ "till_dead ??)?"
    //+ ==> systeme de priorite // "till_dead" ??

