/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:15:47 by febouana          #+#    #+#             */
/*   Updated: 2024/09/10 15:22:49 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//? Permet de trouver le dernier noeud d'une liste.
data_t	*find_last_node(data_t *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

//? Permet d'ajouter un nouvel element nbr a la fin d'une liste.
void	insert_back_dlist(data_t **stack)
{
	data_t	*node;
	data_t	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(data_t));
	if (!node)
		return ;
	node->next = NULL;
    //! besoin de donner des valeurs a philosophers et spoon pour eviter erreurs ??
	if (!(*stack))
	{
		*stack = node;
		node->back = NULL;
	}
	else
	{
		last_node = find_last_node(*stack);
		last_node->next = node;
		node->back = last_node;
	}
}
