#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>


#define MAX_BUFFER 10
#define DATOS_A_PRODUCIR 100

sem_t elementos;
sem_t huecos;
int buffer[MAX_BUFFER];
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
int n_elementos=0;

void Productor(void*);
void Consumidor(void*);

void main(void){

	pthread_t thp1, thp2,thp3,thc1,thc2,thc3;


	sem_init(&elementos, 0, 0);
	sem_init(&huecos, 0,MAX_BUFFER);


	pthread_create(&thp1, NULL, Productor, NULL);
	pthread_create(&thc1, NULL, Consumidor, NULL);

	pthread_join(thp1, NULL);
	pthread_join(thc1, NULL);
	
	
	sem_destroy(&huecos);
	sem_destroy(&elementos);
	
	exit(0);
}



void Productor(void *x){
	int pos=0;
	int dato=0;
	int i;
	printf("Soy el proceso con pid:%i\n", pthread_self());
	
	for(i=0;i<DATOS_A_PRODUCIR;i++){
		dato=dato+1;
		//producir un dato
		pthread_mutex_lock(&mutex);
		//accediendo al buffer
		while(n_elementos==MAX_BUFFER)
			c_wait(lleno,mutex);
		buffer[pos]=dato;
		printf("El dato colocado es:%i\n",buffer[pos]);
		pos=(pos+1)%MAX_BUFFER;
		n_elementos++;
		if(n_elementos==1)
		c_signal(vacio);
		pthread_mutex_unlock(&mutex);
	}
}

void Consumidor(void *x){
	int pos=0;
	int i;
	printf("Soy el proceso con pid:%i\n", pthread_self());
	
	for(i=0;i<DATOS_A_PRODUCIR;i++){
		pthread_mutex_lock(&mutex);
		//accediendo al buffer
		while(n_elementos==0)
			c_wait(vacio,mutex);
		dato=buffer[pos];
		printf("Dato consumido:%i\n",dato);
		pos=(pos+1)%MAX_BUFFER;
		n_elementos--;
		if(n_elemetnos==(MAX_BUFFER-1));
			c_signal(lleno);
		pthread_mutex_unlock(&mutex);
	}
}
