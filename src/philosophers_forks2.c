/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_forks2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:06:01 by febouana          #+#    #+#             */
/*   Updated: 2024/10/15 15:28:34 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lock_forks(t_data *data, int id)
{
	pthread_mutex_lock(&data->philosophers[id].fork_l);
	data->philosophers[id].left_locked = true;
	if (stop_signal(data, data->philosophers[id].is_dead))
	{
		direction_unlock_forks(data, id);
		return ;
	}
	ft_print(data, 0, id, get_current_time(data, id) - data->start_time);
	pthread_mutex_lock(data->philosophers[id].fork_r);
	data->philosophers[id].right_locked = true;
	if (stop_signal(data, data->philosophers[id].is_dead))
	{
		direction_unlock_forks(data, id);
		return ;
	}
	ft_print(data, 0, id, get_current_time(data, id) - data->start_time);
}

void	lock_forks_odd(t_data *data, int id)
{
	pthread_mutex_lock(data->philosophers[id].fork_r);
	data->philosophers[id].right_locked = true;
	if (stop_signal(data, data->philosophers[id].is_dead))
		return ;
	ft_print(data, 0, id, get_current_time(data, id) - data->start_time);
	pthread_mutex_lock(&data->philosophers[id].fork_l);
	data->philosophers[id].left_locked = true;
	if (stop_signal(data, data->philosophers[id].is_dead))
		return ;
	ft_print(data, 0, id, get_current_time(data, id) - data->start_time);
}

void	unlock_forks(t_data *data, int id)
{
	if (data->philosophers[id].left_locked == true)
	{
		pthread_mutex_unlock(&data->philosophers[id].fork_l);
		data->philosophers[id].left_locked = false;
	}
	if (data->philosophers[id].right_locked == true)
	{
		pthread_mutex_unlock(data->philosophers[id].fork_r);
		data->philosophers[id].right_locked = false;
	}
}

void	unlock_forks_odd(t_data *data, int id)
{
	if (data->philosophers[id].right_locked == true)
	{
		pthread_mutex_unlock(data->philosophers[id].fork_r);
		data->philosophers[id].right_locked = false;
	}
	if (data->philosophers[id].left_locked == true)
	{
		pthread_mutex_unlock(&data->philosophers[id].fork_l);
		data->philosophers[id].left_locked = false;
	}
}
