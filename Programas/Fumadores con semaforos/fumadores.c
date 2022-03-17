//Autor: Andres Rafael Escala Acosta
//Semaforos 3: La adiccion mata
//Tabaco: 0
//Cerillos: 1
//Papel: 2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
sem_t agente;
sem_t fumador_tabaco;
sem_t fumador_papel;
sem_t fumador_cerillo;

void Agente(void*);
void Fumador_papel(void*);
void Fumador_tabaco(void*);
void Fumador_cerillos(void*);

void main(void){
    pthread_t th_agente, th_fumT1, th_fumP1, th_fumC1;
    printf("\n\t-----Semaforos 3: La adiccion mata-----\n\n");
    /*inicializar los semaforos */
    sem_init(&agente,0,1);
    sem_init(&fumador_papel,0,0);
    sem_init(&fumador_cerillo,0,0);
    sem_init(&fumador_tabaco,0,0);

    /* crear los procesos ligeros*/
    pthread_create(&th_agente,NULL,(void*)Agente,NULL);
    pthread_create(&th_fumC1,NULL,(void*)Fumador_cerillos,NULL);
    pthread_create(&th_fumP1,NULL,(void*)Fumador_papel,NULL);
    pthread_create(&th_fumT1,NULL,(void*)Fumador_tabaco,NULL);

    /*esperar su finalizacion*/
    pthread_join(th_agente,NULL);
    pthread_join(th_fumC1,NULL);
    pthread_join(th_fumP1,NULL);
    pthread_join(th_fumT1,NULL);

    sem_destroy(&agente);
    sem_destroy(&fumador_tabaco);
    sem_destroy(&fumador_papel);
    sem_destroy(&fumador_cerillo);
    exit(0);
}

void Agente(void *x)
{
    while(1){
        sem_wait(&agente);
        int ing1=0,ing2=0;
        printf("\nSoy el agente: %li\n",pthread_self());
        do{
            ing1=rand()%3;
            ing2=rand()%3;
        }while(ing1==ing2);
        if(ing1==0&&ing2==1||ing2==0&&ing1==1){
            printf("\nLos ingredientes son: Tabaco y Cerillos\n");
            sem_post(&fumador_papel);
            // sem_wait(&agente);
        }
        if(ing1==0&&ing2==2||ing2==0&&ing1==2){
            printf("\nLos ingredientes son: Tabaco y Papel\n");
            sem_post(&fumador_cerillo);
            // sem_wait(&agente);
        }
        if(ing1==1&&ing2==2||ing2==1&&ing1==2){
            printf("\nLos ingredientes son: Papel y Cerillos\n");
            sem_post(&fumador_tabaco);
            // sem_wait(&agente);
        }
    }
    
}

void Fumador_papel(void* x)
{
	while(1){
        int time=0;
        time=1+rand()%3;
        sem_wait(&fumador_papel);
        printf("\nSoy el fumador: %li. Mi ingrediente es el papel. Time: %d\n",pthread_self(),time);
        sleep(time);
        sem_post(&agente);
    }
}

void Fumador_tabaco(void* x)
{
	while(1){
        int time2=0;
        time2=1+rand()%3;
        sem_wait(&fumador_tabaco);
        printf("\nSoy el fumador: %li. Mi ingrediente es el Tabaco. Time: %d\n",pthread_self(),time2);
        sleep(time2);
        sem_post(&agente);
    }
}

void Fumador_cerillos(void* x){
	while(1){
        int time3=0;
        time3=1+rand()%3;
        sem_wait(&fumador_cerillo);
        printf("\nSoy el fumador: %li. Mi ingrediente es el cerillo. Time: %d\n",pthread_self(),time3);
        sleep(time3);
        sem_post(&agente);
    }
}