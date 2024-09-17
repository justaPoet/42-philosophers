/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:38:53 by febouana          #+#    #+#             */
/*   Updated: 2024/09/17 19:28:49 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void error_prompt()
{
    //free(data);
    ft_putstr_fd("\033[31m$> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([number_of_times_each_philosopher_must_eat])\033[0m\n", 2);
}

// void error_prompt(data_t *data)
// {
//     //free(data);
//     ft_putstr_fd("\033[31m$> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] ([number_of_times_each_philosopher_must_eat])\033[0m\n", 2);
// }

void error_forks(data_t *data)
{
	destroy_fork(*data); //! peux possiblement free des fork meme pas allouer et segment
	free(data->philosophers); //OKOK
    //free(data); //OKOK
}

void good_ending(data_t *data)
{
    destroy_fork(*data);
    	//test_fork(*data); //fail a fork DONC mutex bien detruit 
	free(data->philosophers);
    //free(data);
}

//! doit creer un derive de destroy_fork() qui detruit uniquement ceux ayant eu le temps d'etre crees dans create_foeks sinon: 
//! "Conditional jump or move depends on uninitialised value(s)"
