/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:52:56 by febouana          #+#    #+#             */
/*   Updated: 2024/09/20 03:23:02 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// 1 🍴 takes forks
// 2 🍝 is_eating
// 3 💤 is_sleeping
// 4 🤔 is_thinking (apres sleep oeoe)
// 5 ☠️  IS DEAD

//! CAS CALCULER SI PHILO IMPAIR OU PAIR DE BASE ET QUELLE GRP FAIRE MANGE EN PREMIER EST LE PLUS OPTI
void complet_routine(data_t *data, int id)
{     
    if (id % 2 != 0)
        usleep(data->time_to_eat * 1000);
    while(1)
    {    
    printf("(%d)>>>lastmeal==%lld | ", id + 1, data->philosophers[id].last_meal); 
    printf("(%d)>>>lastlastmeal==%lld\n", id + 1, data->philosophers[id].last_last_meal);  
    printf("(%d)>>>LASTMEAL-LASTLASTMEAL==%lld\n\n", id + 1, data->philosophers[id].last_meal - data->philosophers[id].last_last_meal);   
      
    if (data->time_to_die <= (data->philosophers[id].last_meal - data->philosophers[id].last_last_meal))
    {
        printf("\n\n☠️ ISSSSSS DEAD =======================================================\n\n");
        exit(2);   
    }
        
//? DEBUT        
    data->philosophers[id].will_eat = true;    
//? is_taking_fork_l (la sienne)
    data->philosophers[id].is_taking_fork_l = true;
    pthread_mutex_lock(&data->philosophers[id].fork_l);
    printf("%lld 🍴 (%d) took the left fork\n", get_current_time() - data->start_time, id + 1);
            
//? is_taking_fork_r (celle du philo de droite)
    data->philosophers[id].is_taking_fork_r = true;
    pthread_mutex_lock(data->philosophers[id].fork_r);
    printf("%lld 🍴 (%d) took the right fork\n", get_current_time() - data->start_time, id + 1);
        
//? is_eating
    printf("%lld 🍝 (%d) is eating\n", get_current_time() - data->start_time, id + 1);
    usleep(data->time_to_eat * 1000);
    data->philosophers[id].repeat_meal_philo--;
    
    data->philosophers[id].last_last_meal = data->philosophers[id].last_meal;     
    data->philosophers[id].last_meal = get_current_time() - data->start_time; //+ marque le temps qui s'est ecoule depuis debut du prog ou philo a manger pour la dernier foi

//? put down fork_l and fork_r
    pthread_mutex_unlock(&data->philosophers[id].fork_l); 
    data->philosophers[id].is_taking_fork_l = false;
    pthread_mutex_unlock(data->philosophers[id].fork_r);
    data->philosophers[id].is_taking_fork_r = false;
        
//? FIN
    data->philosophers[id].will_eat = false;
    printf("%lld 💤 (%d) is sleeping\n", get_current_time() - data->start_time, id + 1);
    usleep(data->time_to_sleep * 1000); //OKOK
    printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
}}

//? Creer routine : manger / dormir / penser
void	*philosopher_routine(void *index)
{
	//! cas si qu'1 seul philo // if (data->nbr_philos == 1) ou if (fork_l == fork_r)

    data_t *data;
    data = get_data();
    int id = *(int*)index - 1; //pour revenir a un index propre
    

    complet_routine(data, id);
    

    // die(data, id)
    // sleeping(data, id);
    // thinking(data, id);
    
	return (NULL);
}






    

// le premier prio a manger est le philo 1
// comprendre fn temporalite

// void *philosopher_routine(data_t *data)
// {
//     // if (data->nbr_philos == 1)
//     // {
//     //     ft_putstr_fd("a philo is dead.\n", 2);
//     //     return (NULL);
//     // }
//     printf("philo commence a gimgembre\n");
//     printf("philo a fini de gimgembre\n");

//     return (NULL);
// }



// void complet_routine(data_t *data, int id)
// {
//     if (id % 2 != 0) // OKOK
//     {
//         usleep(data->time_to_eat * 1000); //OKOK
//     }


        
//     //while (1)
//     //{
           
//         //! probleme sans ca ??
//         //! ========================================================================================================================================== bien pas bien ???
//         // if (id == 0)
//         //     while (data->philosophers[data->nbr_philos].will_eat == true || data->philosophers[1].will_eat == true)
//         //         usleep(1);		
//         // if (id == data->nbr_philos)
//         //     while (data->philosophers[data->nbr_philos - 1].will_eat == true || data->philosophers[0].will_eat == true)
//         //         usleep(1);
//         // else
//         //     while (data->philosophers[id - 1].will_eat == true || data->philosophers[id + 1].will_eat == true)
//         //         usleep(1);
//         //! ========================================================================================================================================== bien pas bien ???
        
//         if ((data->time_to_die) >= ((get_current_time() - data->start_time ) + data->philosophers[id].last_meal)) //! condition pour voir si mort 
//         {
//             //! if (data->philosophers[id - 1].is_taking_fork_r == false && data->philosophers[id + 1].is_taking_fork_l == false) //! probleme si id == 0 || id == nbr_philos
//             //? DEBUT        
//                 data->philosophers[id].will_eat = true;
                
//             //? is_taking_fork_l (la sienne)
//                 data->philosophers[id].is_taking_fork_l = true;
//                 pthread_mutex_lock(&data->philosophers[id].fork_l);
//                 printf("%lld 🍴 (%d) took the left fork\n", get_current_time() - data->start_time, id + 1);
                
//             //? is_taking_fork_r (celle du philo de droite)
//                 data->philosophers[id].is_taking_fork_r = true;
//                 pthread_mutex_lock(data->philosophers[id].fork_r);
//                 printf("%lld 🍴 (%d) took the right fork\n", get_current_time() - data->start_time, id + 1);
            

                                 
//         // //if ((data->time_to_die) <= ((get_current_time() - data->start_time ) + data->philosophers[id].last_meal))
//         // if ((data->time_to_die) <= get_current_time() - data->start_time - data->philosophers->last_meal)
//         // {
//         //     // printf("\n\n==================(%d)>>>TIME==%lld\n\n", id + 1,(get_current_time() - data->start_time ) + data->philosophers[id].last_meal);    
//         //     // printf("\n\n==================(%d)>>>TIME==%lld\n\n", id + 1, get_current_time() - data->start_time);    
//         //     printf("\n\n☠️ IS DEAD =======================================================\n\n");
//         //     exit(2);   
//         // }

//         // printf("\n\n(%d)>>>TIME==%lld\n\n", id + 1, get_current_time() - data->start_time - data->philosophers->last_meal); 
        
//             //? is_eating
//                 printf("%lld 🍝 (%d) is eating\n", get_current_time() - data->start_time, id + 1);
//                 usleep(data->time_to_eat * 1000);
//                 data->philosophers[id].repeat_meal_philo--;
//                 data->philosophers[id].last_meal = get_current_time() - data->start_time; // marque le temps qui s'est ecoule depuis debut du prog ou philo a manger pour la dernier fois
    
//             //? put down fork_l and fork_r
//                 pthread_mutex_unlock(&data->philosophers[id].fork_l); 
//                 data->philosophers[id].is_taking_fork_l = false;
//                 pthread_mutex_unlock(data->philosophers[id].fork_r);
//                 data->philosophers[id].is_taking_fork_r = false;
                
//             //? FIN
//                 data->philosophers[id].will_eat = false;
                
//                 printf("%lld 💤 (%d) is sleeping\n", get_current_time() - data->start_time, id + 1);
//                 usleep(data->time_to_sleep * 1000); //OKOK
//                 printf("%lld 🤔 (%d) is thinking\n", get_current_time() - data->start_time, id + 1);
//         }
//         // else // is_dead
//         // {
//         //     printf("\n\n☠️ (%d) IS DEAD =======================================================\n\n", id);
//         //     exit(2);    
//         // }
//    // }
//     }