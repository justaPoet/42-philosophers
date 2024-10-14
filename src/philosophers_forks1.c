/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_forks1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:39:05 by febouana          #+#    #+#             */
/*   Updated: 2024/10/14 20:06:57 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	create_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_mutex_init(&data->philosophers[i].fork_l, NULL) != 0)
		{
			error_quit(data, i);
			return (2);
		}
		i++;
	}
	assign_fork(data);
	return (0);
}

int	direction_lock_forks(t_data *data, int id)
{
	if (data->philosophers[id].id % 2 == 0)
		lock_forks(data, id);
	else
		lock_forks_odd(data, id);
	return (0);
}

void	direction_unlock_forks(t_data *data, int id)
{
	if (data->philosophers[id].id % 2 == 0)
		unlock_forks(data, id);
	else
		unlock_forks_odd(data, id);
}
