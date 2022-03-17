//Semaforos 2: La secuela
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
sem_t lector;
sem_t escritor;
int variable_compartida=0;
int contador = 0;

void Escritor(void*);
void Lector(void*);

void main(void){
    pthread_t th1, th2, th3, th4;
    printf("\n\t-----Semaforos 2: La secuela-----\n\n");
    /*inicializar los semaforos */
    sem_init(&lector,0,1);
    sem_init(&escritor,0,1);

    /* crear los procesos ligeros*/
    pthread_create(&th1,NULL,(void*)Escritor,(void*)1);
    pthread_create(&th2,NULL,(void*)Lector,(void*)1);
    pthread_create(&th3,NULL,(void*)Escritor,(void*)2);
    pthread_create(&th4,NULL,(void*)Lector,(void*)2);

    /*esperar su finalizacion*/
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);

    sem_destroy(&escritor);
    sem_destroy(&lector);
    exit(0);
}

void Escritor(void *achu){

    while(1){
		sem_wait(&escritor);
			printf("\nSoy el escritor %i  con PID: %li\n", (int*) achu, pthread_self());
			printf("\nEl valor de la variable_compartida es: %d\n",variable_compartida);	
            variable_compartida+=2;
            printf("\nEl nuevo valor de la variable_compartida es: %d\n\n---------------------------------\n",variable_compartida);		
		sem_post(&escritor);
		sleep(1);
	}
}

void Lector(void *achu){
    while(1){
		sem_wait(&lector);
			contador+=2;
			if (contador == 2){
                sem_wait(&escritor);
            }
				
		sem_post(&lector);
			printf("\nSoy el lector %i con PID: %li\n", (int*)achu, pthread_self());
            printf("\nEl valor de la variable_compartida es: %d\n", variable_compartida);
		sem_wait(&lector);
		contador-=2;
		if(contador==0)
			sem_post(&escritor);
		sem_post(&lector);
		sleep(1);		
	}
}