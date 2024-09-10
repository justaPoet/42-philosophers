#include <pthread.h>
#include <stdio.h>  //printf
#include <stdlib.h> //malloc+free
#include <string.h> //memset
#include <unistd.h> //usleep

// typedef struct philodata
// {
// 	pthread_t		*philosophers;
// 	pthread_mutex_t	*spoons;

// }					data_t;

typedef struct philo_data
{
	pthread_t		        	philosopher;
	pthread_mutex_t	        	spoon;

    int 				position_order;

	struct philo_data	        *next;
	struct philo_data	        *back;
}					        data_t;
