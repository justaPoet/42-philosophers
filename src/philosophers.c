/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:49:20 by febouana          #+#    #+#             */
/*   Updated: 2024/09/19 21:11:58 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
    //* printf("-----------------------------------\n");
    //* printf("| PHILO N* |   ROUTINE            |\n");
    //* printf("-----------------------------------\n");

    if (data.start_time == -1)
        return ; //! gestion_errors

    while (i < data.nbr_philos)
    {
        //data.philosophers[i].is_till_dead = false;
        data.philosophers[i].repeat_meal_philo = data.repeat_meal; 
        data.philosophers[i].last_meal = 0; 
        data.philosophers[i].philo_id = i + 1; // normalement apres secu mais besoin dans routine
        if (pthread_create(&data.philosophers[i].philo, NULL, &philosopher_routine, &data.philosophers[i].philo_id) != 0)
            return ;  //! GESTION ERROR //+ destroy   
        // printf("TRUE-PHILO-ID(%d)\n", data.philosophers[i].philo_id);
        // printf("\n");
        i++;
    }   
}

void assign_fork(data_t data)
{
    int i;

    i = 0;
    while (i < data.nbr_philos - 1)
    {
        data.philosophers[i].fork_r = &data.philosophers[i + 1].fork_l; //! VERIFIER SI PAS DE DEBORDEMENT ET QUE philo[nbr_philos] PAS DE PROBLEME
        i++;
    }
    data.philosophers[i].fork_r = &data.philosophers[0].fork_l;
} 

int create_forks(data_t data)
{
    int i;
    
    i = 0;
    while (i < data.nbr_philos)
    {
        if (pthread_mutex_init(&data.philosophers[i].fork_l, NULL) != 0)
        {
            error_forks(&data); //! peux possiblement free des fork meme pas allouer et segment
            return (2);
        }
        i++;
    }   
    assign_fork(data);
    return (0);
}

int parsing_args(data_t **data, int argc, char **args)
{
    (*data)->nbr_philos = ft_atol(args[1]);
    if ((*data)->nbr_philos > 200 || (*data)->nbr_philos == 0)
    {
        error_prompt();
        return (2); 
    }
    (*data)->time_to_die = ft_atol(args[2]);
    (*data)->time_to_eat = ft_atol(args[3]);
    (*data)->time_to_sleep = ft_atol(args[4]);
    (*data)->start_time = get_current_time();
    if (argc == 6)
    {
        (*data)->repeat_meal = ft_atol(args[5]);
        if ((*data)->repeat_meal == 0)
        {
            error_prompt();
            return (2); 
        }
    }
    else
        (*data)->repeat_meal = -1;
    return (0);
}

int	verif_args(char **args)
{
	int	x;
	int	i;

	x = 1;
	while (args[x])
	{
		i = 0;
		while (args[x][i])
		{
			if (!(args[x][i] >= '0' && args[x][i] <= '9'))
            {
                error_prompt();
                return (2);    
            }
			i++;
		}
		x++;
	}
    return (0);
}

int main(int argc, char **argv)
{     
    data_t *data;
    data = get_data();
    
    if (argc < 5 || 6 < argc)
        return (2);
    if (verif_args(argv) == 2)
        return (2);
    if (parsing_args(&data, argc, argv) == 2)
        return (2);
    //init_vars(); // initialiser toutes les vars de la struct proprement
    data->philosophers = malloc(data->nbr_philos * sizeof(philo_status_t));
    if (!data->philosophers)
    {
        error_prompt();
        return (2);
    }
    if (create_forks(*data) == 2)
        return (2);
    create_philosophers(*data);
    join_philosophers(*data);
    good_ending(data);

    //? Each philosopher ate X time(s)
}

//! doit creer un derive de destroy_fork() qui detruit uniquement ceux ayant eu le temps d'etre crees dans create_foeks sinon: 
//! "Conditional jump or move depends on uninitialised value(s)"

//? si il n'y a qu'un seul philo fork_r == fork_l ATTENTION AUX DEADLOCK ET PREVOIR UN CAS A PART PENDANT L'ALGO
//+ CODER ALGO:
    //+ ==> routine precise phil (manger, dormir, penser)
        //+ // systeme d'etat "is_eating" + "is_dead" (+ "till_dead ??)?"
    //+ ==> systeme de priorite // "till_dead" ??


// void test_fork(data_t data)
// {
//     int i = 0;

//     while (i < data.nbr_philos)
//     {
//         // Tester la fourchette gauche
//         if (pthread_mutex_trylock(&data.philosophers[i].fork_l) == 0)
//         {
//             printf("==> Fork LEFT confirmed (%d)\n", i + 1);
//             pthread_mutex_unlock(&data.philosophers[i].fork_l);
//         }
//         else
//             printf("==> Failed to lock LEFT fork (%d)\n", i + 1);
//         // Tester la fourchette droite
//         if (pthread_mutex_trylock(data.philosophers[i].fork_r) == 0)
//         {
//             printf("==> Fork RIGHT confirmed (%d)\n", i + 1);
//             pthread_mutex_unlock(data.philosophers[i].fork_r);
//         }
//         else
//             printf("==> Failed to lock RIGHT fork (%d)\n", i + 1);
//         i++;
//     }   
// }
