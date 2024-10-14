/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_memento_mori.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 22:30:24 by febouana          #+#    #+#             */
/*   Updated: 2024/10/14 20:18:38 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_bool	stop_signal(t_data *data, t_bool dead)
{
	pthread_mutex_lock(&data->m_stop);
	if (data->stop == true)
	{
		dead = true;
		pthread_mutex_unlock(&data->m_stop);
		return (true);
	}
	pthread_mutex_unlock(&data->m_stop);
	return (false);
}

void	will_die(t_data *data, long long int time_death, int id)
{
	pthread_mutex_lock(&data->m_stop);
	if (data->stop == false)
	{
		data->stop = true;
		unlock_forks(data, id);
		ft_usleep(data, time_death, id);
		ft_print(data, 4, id, get_current_time(data, id) - data->start_time);
		data->philosophers[id].is_dead = true;
	}
	pthread_mutex_unlock(&data->m_stop);
}

long long	get_start_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return (milliseconds);
}

void	time_stop(t_data *data, int id)
{
	pthread_mutex_lock(&data->m_stop);
	if (data->stop == false)
	{
		data->stop = true;
		unlock_forks(data, id);
		data->philosophers[id].is_dead = true;
		ft_print(data, -1, id, get_current_time(data, id) - data->start_time);
	}
	pthread_mutex_unlock(&data->m_stop);
}

int	routine_solo(t_data *data, int id)
{
	pthread_mutex_lock(&data->philosophers[id].fork_l);
	data->philosophers[id].left_locked = true;
	ft_print(data, 0, id, get_current_time(data, id) - data->start_time);
	will_die(data, data->time_to_die, id);
	return (0);
}
