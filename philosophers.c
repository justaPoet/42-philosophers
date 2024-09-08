/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:55:52 by apoet             #+#    #+#             */
/*   Updated: 2024/09/08 22:40:19 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//? demo avec 5 philo sans main/argc/argv

#include <stdio.h> //printf
#include <stdlib.h> //malloc / free
#include <string.h> //memset
#include <pthread.h>

//int ft_waiter_checker()
//==> verifie si les forks/spoons du philo passer en arg sont libres
// return 0 si le philo peut manger 1 si non

//! Le pthread_join() free les threads ???

void philo_routine()
{
    printf("philo commence a gimgembre\n", "\e[1;33m");
    sleep(1);
    printf("philo a fini de gimgembre\n", "\e[1;33m");
}

int main()
{ 
    int nbr_philo = 5;
    pthread_t philos[nbr_philo];

    int i = 0;
    while (i < nbr_philo)
    {
        if (pthread_create(&philos[i], NULL, philo_routine, NULL) != 0)
            return (1);
        printf("main : philo(%d) created\n", i + 1);            
        i++;
    }

    i = 0;
    while (i < nbr_philo) //? boucle potentiellement inutile (reesayer sans + relire fonctionne de pthread_join) 
    {
        if (pthread_join(philos[i], NULL) != 0)
            return (1);
        printf("main : philo(%d) joined\n", i + 1);    
        i++;
    }
    return (0);
}

// memset == a utiliser au moment d'initialiser une variable pour passer chaque valeur a 0 et ainsi eviter les possibles erreurs 
// gettimeofday == sert a lire ou programmer l'heure ainsi que le fuseau horaire //+ => va nous premettre de gerer les limites de temps imposes par le sujet 

// pthread_mutex_init == permet d'inistialiser un mutex //+ => va nous permettre de verrouiller les spoons quand on en aura besoin et aussi pour eviter les deadlocks
// pthread_mutex_destroy == permet de detruire le mutex de poser //+
// pthread_mutrex_lock == permet de verrouille la variable precisee //+ 
// pthread_mutex_unlock == permet de deverouille la variable precisee precedemment bloque //+

// pthread_create == permet de creer un thread lorsqu'on lui donne une variable de type pthread_t //+ permet de creer chaque philosophe sous forme de thread
// pthread_detach == permet de placer un thread en etat detache. Cela garantit que les ressources memoires consommees seront immediatement liberees lorsque l'execution s'achevera. //? utile en fin de programme pour eviter les leaks ?????
// pthread_join == permet de mettre en suspend l'execution du thread appelant jusqu'q ce que le thread identifie par le premier arg acheve son execution //? ==> sorte de wait() mais pour les threads

//? NB : il existe deux etats pour un thread, joignable et injoignable. 
//? Il devient injoignable a cause de pthread_detach(),
//? et ainsi prhtread_join() ne peux plus etre utilise par exemple.


//==============

// essayer un mutex ?
// essayer d'implanter les spoons