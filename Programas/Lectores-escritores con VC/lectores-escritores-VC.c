//Autor: Andres Rafael Escala Acosta
//PROGRAMA LECTORES-ESCRITORES con variables de condicion

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
int elementos= 0;
int bandera = 0;
int variable_modificar = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lector = PTHREAD_COND_INITIALIZER;
pthread_cond_t escritor = PTHREAD_COND_INITIALIZER;
// pthread_cond_wait(&varcondicion, &mutex);
// int pthread_cond_signal(pthread_cond_t * restrict cond);
// 	pthread_cond_signal(&varcondicion);
// int pthread_cond_destroy(pthread_cond_t * restrict cond);
// 	pthread_cond_destroy(&varcondicion);
// int pthread_cond_broadcast(pthread_cond_t * restrict cond);
// int pthread_cond_init(pthread_cond_t*restrict cond, pthread_condattr_t * restrict attr);

void* Lectura(void*);
void* Escritura(void*);

void main(){
	
	//Hilos lectores
	pthread_t th_lec1, th_lec2;
	//Hilos escritores
	pthread_t th_esc1, th_esc2;
	
	/*Crear los procesos ligeros del productor*/
	pthread_create(&th_esc1, NULL, Escritura, (void*) 1);
	pthread_create(&th_esc2, NULL, Escritura, (void*) 2);
	
	/*Crear los procesos ligeros del consumidor*/
	pthread_create(&th_lec1, NULL, Lectura,(void*) 1);
	pthread_create(&th_lec2, NULL, Lectura,(void*) 2);
	
	
	/* Esperar su finalizaciÃ²n*/
	pthread_join(th_esc1, NULL);
	pthread_join(th_esc2, NULL);
	pthread_join(th_lec1, NULL);
	pthread_join(th_lec2, NULL);
	
	pthread_cond_destroy(&lector);
	pthread_cond_destroy(&escritor);
	
	exit(0);
}


void* Escritura(void* variable){

	while(1){
			
        pthread_mutex_lock(&mutex); 
		
		if(elementos>0){
			pthread_cond_wait(&escritor, &mutex);

		}
		bandera=1;
		printf("El PID del escritor %i es %li y la variable antes de modificar es %i\n", (int*) variable, pthread_self(), variable_modificar);
		variable_modificar++;
			
		printf("El PID del escritor %i es %li y la variable modificada es %i\n", (int*) variable, pthread_self(), variable_modificar);
		
		sleep(1);
		bandera=0;
		pthread_cond_signal(&lector);
		pthread_mutex_unlock(&mutex);
	}
}


void* Lectura(void* variable){
	
	while(1){
		
		pthread_mutex_lock(&mutex); 
		elementos++;
		if(bandera==1){
			pthread_cond_wait(&lector, &mutex);
		}
			
		pthread_mutex_unlock(&mutex); 
		printf("El PID del lector %i es %li y la variable es %i\n", (int*) variable, pthread_self(), variable_modificar);

		pthread_mutex_lock(&mutex);
		elementos--;
		 
		if(elementos==0)
		{
			pthread_cond_signal(&escritor);
		}
		pthread_mutex_unlock(&mutex);
		
				
	}
	
}