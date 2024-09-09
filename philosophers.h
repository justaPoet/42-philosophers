#include <stdio.h> //printf
#include <stdlib.h> //malloc + free
#include <string.h> //memset
#include <pthread.h>

typedef struct philodata
{
    pthread_t *φ;
}                   data_t;
