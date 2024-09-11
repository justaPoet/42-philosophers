/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:15:47 by febouana          #+#    #+#             */
/*   Updated: 2024/09/11 15:41:36 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//! NE PAS GARDER 
void print_dlist(table_t **stack)
{
    if (stack == NULL || *stack == NULL)
    {
        printf("stack is empty.\n");
        return ;
    }
    table_t *current = *stack;
    printf("LIST== ");
    while (current->next != NULL)
    {
        printf("|%ld|  ", current->position_order);
        current = current->next;
    }
    printf("\n");
}

//? Permet de trouver le dernier noeud d'une liste.
table_t	*find_last_node(table_t *philo)
{
	if (philo == NULL)
		return (NULL);
	while (philo->next)
		philo = philo->next;
	return (philo);
}
//? Permet d'ajouter un nouvel element nbr a la fin d'une liste.
//! besoin de donner des valeurs aux vars struct pour eviter erreurs ?????
void	insert_back_dlist(table_t **list, int nbr)
{
	table_t	*philo;
	table_t	*last_philo;

	if (!list)
	{
    printf("Memory allocation failed\n");
    return;
}
	philo = malloc(sizeof(table_t));
	if (!philo)
		return ;
	philo->next = NULL;
    philo->position_order = nbr;
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
























//! A REFAIRE================================================================================================================================
//! Pour quitter le programme proprement et eviter toute erreur

// //? Permet de supprime le premier element d'une liste.
// void	del_front_dlist(t_Stack **stack)
// {
// 	t_Stack	*del_node;
// 	t_Stack	*new_first;

// 	if (stack == NULL || *stack == NULL)
// 		return ;
// 	del_node = *stack;
// 	new_first = del_node->next;
// 	if (new_first)
// 		new_first->back = NULL;
// 	*stack = new_first;
// 	del_node->next = NULL;
// 	del_node->back = NULL;
// 	free(del_node);
// }

// //? Maki Zenin permet de TOUT DETRUIRE.
// void	maki_zenin(t_Stack **stack)
// {
// 	if (stack == NULL || *stack == NULL)
// 		return ;
// 	while (*stack != NULL)
// 		del_front_dlist(stack);
// }

