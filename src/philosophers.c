/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:49:20 by febouana          #+#    #+#             */
/*   Updated: 2024/09/16 20:48:46 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


//? Creer routine : manger / dormir / penser 
//! + cas a part si qu'un seul philo (probleme fourchette)
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
            return ;  //! GESTION ERROR //+ destroy   
        data.philosophers[i].philo_id = i + 1;
        i++;
    }   
}

void assign_fork(data_t data)
{
    int i;

    i = 0;
    while (i < data.nbr_philos - 1)
    {
        data.philosophers[i].fork_r = &data.philosophers[i + 1].fork_l;
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
        printf("MUTEX CREE (%d)\n", i + 1);
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
        error_prompt(*data);
        return (2); 
    }
    (*data)->time_to_die = ft_atol(args[2]);
    (*data)->time_to_eat = ft_atol(args[3]);
    (*data)->time_to_sleep = ft_atol(args[4]);
    if (argc == 6)
    {
        (*data)->repeat_eat = ft_atol(args[5]);
        if ((*data)->repeat_eat == 0)
        {
            error_prompt(*data);
            return (2); 
        }
    }
    else
        (*data)->repeat_eat = 1;
    return (0);
}

int	verif_args(data_t *data, char **args)
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
                error_prompt(data);
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
    
    if (argc < 5 || 6 < argc)
        return (2);
    data = malloc(sizeof(data_t));
    if (!data)
        return (2);
    if (verif_args(data, argv) == 2)
        return (2);
    if (parsing_args(&data, argc, argv) == 2)
        return (2);
    data->philosophers = malloc(data->nbr_philos * sizeof(philo_status_t));
    if (!data->philosophers)
    {
        error_prompt(data);
        return (2);
    }
    if (create_forks(*data) == 2)
        return (2);
    create_philosophers(*data);
    join_philosophers(*data);
    good_ending(data);
}

//! rajouter un verif_args() a la push swap pour exclure tout ce qui n'est pas entre 0 et 9
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
