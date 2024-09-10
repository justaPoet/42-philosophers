#include "philosophers.h"

void print_dlist(data_t **stack)
{
    if (stack == NULL)
    {
        printf("stack is empty.\n");
        return ;
    }
    data_t *current = *stack;
    printf("LIST== ");
    while (current->next != NULL)
    {
        printf("|%d|  ", current->position_order);
        current = current->next;
    }
    printf("\n");
}

//? Permet de trouver le dernier noeud d'une liste.
data_t	*find_last_node(data_t *philo)
{
	if (philo == NULL)
		return (NULL);
	while (philo->next)
		philo = philo->next;
	return (philo);
}

//? Permet d'ajouter un nouvel element nbr a la fin d'une liste.
void	insert_back_dlist(data_t **list, int nbr)
{
	data_t	*philo;
	data_t	*last_philo;

	if (!list)
		return ;
	philo = malloc(sizeof(data_t));
	if (!philo)
		return ;
	philo->next = NULL;
    philo->position_order = nbr;
    //? besoin de donner des valeurs aux vars struct pour eviter erreurs ??
	if (!(*list))
	{
		*list = philo;
		philo->back = NULL;
	}
	else
	{
		last_philo = find_last_node(*list);
		last_philo->next = philo;
		philo->back = last_philo;
	}
}

//!=============================================================================================






















// void create_spoons_ptr(data_t data, int nbr_philo)
// {
//     int i;
    
//     i = 0;
//     data.spoons[nbr_philo];
//     while (i < nbr_philo)
//         data.spoons[++i] = i + 1;  
//     //printf("SPOONS==%d\n", i);
// }

// void create_philosophers(data_t *list, int nbr_philos)
// {
//     int i;

//     i = 1;
//     while(i <= nbr_philos)
//     {
//         printf("NBR_PHILOS==%d | I==%d\n", nbr_philos, i);

//         print_dlist(&list);
//         printf("\n");        

//         insert_back_dlist(list, i);
//         i++;
//     }
//     print_dlist(&list);
// }


// int main()
// { 
//     int nbr_philo = 5;

//     int i;
//     data_t list;

//     create_philosophers(&list, nbr_philo);
//     //create_spoons_ptr(data, nbr_philo);


//     i = 1; //!
//     while (i < nbr_philo)
//     {
//         if (pthread_create(&list.philosopher, NULL, &philosopher_routine, NULL) != 0)
//             return (1);
//         printf("==>PHILO(%d) created\n", list.position_order);
//         list = *list.next;       
//         i++;
//     }
//     i = 1; //!
//     while (list.next)
//     {
//         if (pthread_join(list.philosopher, NULL) != 0)
//             return (1);
//         printf("main : philo(%d) joined\n", i + 1);    
//         list = *list.next; 
//         i++;
//     }

//     return (0);
// }

// int main()
// { 
//     int nbr_philo = 5;
//     data_t data;

//     create_philosophers_ptr(data, nbr_philo);
//     //create_spoons_ptr(data, nbr_philo);
    
//     int i = 0;
//     while (data.philosophers[i])
//     {
//         if (pthread_create(&data.philosophers[i], NULL, &philo_routine, NULL) != 0)
//             return (1);
//         printf("main : philo(%d) created\n", i + 1);            
//         i++;
//     }
//     i = 0;
//     while (data.philosophers[i])
//     {
//         if (pthread_join(data.philosophers[i], NULL) != 0)
//             return (1);
//         printf("main : philo(%d) joined\n", i + 1);    
//         i++;
//     }
//     return (0);
// }

void *philosopher_routine()
{
    printf("philo commence a gimgembre\n");
    printf("philo a fini de gimgembre\n");
    return (NULL);
}

//fonctionne qd un seul thread DONC doit malloc + faire un tab pour gerer multithreads
int main()
{ 
    int nbr_philo = 5;

    //data_t data;
    //data.φ[nbr_philo];

    pthread_t th1;
    pthread_t th2;

    
    if (pthread_create(&th1, NULL, &philosopher_routine, NULL) != 0)
        return (1);
    printf("main : philo created\n");            

    if (pthread_join(th1, NULL) != 0)
        return (1);
    printf("main : philo joined\n");    

    return (0);
}