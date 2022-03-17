//Autor: Andres Rafael Escala Acosta
//PROGRAMA Productores-Consumidores con variables de condicion
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>


#define MAX_BUFFER 10
#define DATOS_A_PRODUCIR 100

int buffer[MAX_BUFFER];
pthread_cond_t lleno = PTHREAD_COND_INITIALIZER;
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
int n_elementos=0;

void* Productor(void*);
void* Consumidor(void*);

void main(void){
	printf("\n\t----Productores y Consumidores----\n");
    pthread_t th1, th2, th3, th4, th5, th6;

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
	
	
	pthread_cond_destroy(&lleno);
	pthread_cond_destroy(&vacio);
	
	
	exit(0);
}



void* Productor(void *achu){
	int pos=0;
	int dato=0;
	int i;
	printf("Soy el proceso con pid:%li\n", pthread_self());
	
	for(i=0;i<DATOS_A_PRODUCIR;i++){
		dato=dato+1;
		//producir un dato
		pthread_mutex_lock(&mutex);
		//accediendo al buffer
		while(n_elementos==MAX_BUFFER)
			pthread_cond_wait(&lleno,&mutex);
		buffer[pos]=dato;
        printf("\nProductor  %i: %li\tDato producido: %i\tPosicion: %i\n",(int*) achu,pthread_self(),buffer[pos],pos);
		pos=(pos+1)%MAX_BUFFER;
		n_elementos++;
		if(n_elementos==1)
		pthread_cond_signal(&vacio);
		pthread_mutex_unlock(&mutex);
	}
}

void* Consumidor(void *achu){
	int posc=0;
	int datoc,j;
	printf("Soy el proceso con pid:%li\n", pthread_self());
	
	for(j=0;j<DATOS_A_PRODUCIR;j++){
		pthread_mutex_lock(&mutex);
		//accediendo al buffer
		while(n_elementos==0)
			pthread_cond_wait(&vacio,&mutex);
		datoc=buffer[posc];
        printf("\nConsumidor %i: %li\tDato consumido: %i\tPosicion: %i\n",(int*) achu,pthread_self(),buffer[posc],posc);
		posc=(posc+1)%MAX_BUFFER;
		n_elementos--;
		if(n_elementos==(MAX_BUFFER-1));
			pthread_cond_signal(&lleno);
		pthread_mutex_unlock(&mutex);
	}
}
