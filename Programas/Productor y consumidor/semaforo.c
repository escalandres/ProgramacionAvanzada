//Autor: Andres Rafael Escala Acosta
//Semaforos 1: Productores y consumidores
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#define MAX_BUFFER 8
#define DATOS_A_PRODUCIR 100
sem_t elementos;
sem_t huecos;
int buffer[MAX_BUFFER];
// int pos=0,posc=0;
// int dato,datoc,i,j;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void Productor(void*);
void Consumidor(void*);

void main(void){
    printf("\n\t----Productores y Consumidores----\n");
    pthread_t th1, th2, th3, th4, th5, th6;

    /*inicializar los semaforos */
    sem_init(&elementos,0,0);
    sem_init(&huecos,0,MAX_BUFFER);

    /* crear los procesos ligeros*/
    pthread_create(&th1,NULL,(void*)Productor,(void*)1);
    pthread_create(&th2,NULL,(void*)Consumidor,(void*)1);
    pthread_create(&th3,NULL,(void*)Productor,(void*)2);
    pthread_create(&th4,NULL,(void*)Consumidor,(void*)2);
    pthread_create(&th5,NULL,(void*)Productor,(void*)3);
    pthread_create(&th6,NULL,(void*)Consumidor,(void*)3);

    /*esperar su finalizacion*/
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);
    pthread_join(th6,NULL);

    sem_destroy(&huecos);
    sem_destroy(&elementos);
    exit(0);
}

void Productor(void *achu){
    int pos=0;
    int dato,i;
    // pthread_mutex_lock(&mutex);
    for(i=0;i<DATOS_A_PRODUCIR;i++){
        dato=i; /*producir dato*/
        /*u hueco menos*/
        sem_wait(&huecos);
        buffer[pos]=i;
        printf("\nProductor  %i: %li\tDato producido: %i\tPosicion: %i\n",(int*) achu,pthread_self(),buffer[pos],pos);
        pos=(pos+1)%MAX_BUFFER;
        // printf("pos: [%d] = %d\n",pos,dato);
        /*+1 elemento*/
        sem_post(&elementos);
    }
    // printf("-------------------\n");
    // pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void Consumidor(void *achu){
    int posc=0;
    int datoc,j;
    // pthread_mutex_lock(&mutex);
    for(j=0;j<DATOS_A_PRODUCIR;j++)
    {
        
        /* un elemento menos*/
        sem_wait(&elementos);
        datoc=buffer[posc];
        printf("\nConsumidor %i: %li\tDato consumido: %i\tPosicion: %i\n",(int*) achu,pthread_self(),buffer[posc],posc);
        // printf("pos: [%d] = %d\n",pos,i);
        posc=(posc+1)%MAX_BUFFER;
        /*un hueco mas*/
        sem_post(&huecos);
    }
    // printf("-------------------\n");
    // pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}