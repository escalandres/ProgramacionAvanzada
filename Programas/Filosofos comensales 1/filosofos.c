//Integrantes:
//Vargas Sánchez Andrea Liliana			
//Cisneros Martínez Daphne Liliana
//Escala Acosta Andres Rafael

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
int sema[5]; //lleva la cuenta de los palillos ocupados y disponibles
sem_t jarra;
//Cada filosofo tiene un palillo con su numero y usa el del otro filosofos a su lado
sem_t palillo1;
sem_t palillo2;
sem_t palillo3;
sem_t palillo4;
sem_t palillo0;

void Comer(void*);
void Beber(void*);
void Pensar(void*);
void Filosofo(void*);

void main(void){
    int i=0;
    for(i=0;i<5;i++){
        sema[i]=1;
        //Todos los palillos estan disponibles al inicio
    }
    pthread_t th_f1, th_f2, th_f3, th_f4, th_f0;
    printf("\n\t-----Filosofos chinos-----\n\n");
    /*inicializar los semaforos */
    sem_init(&jarra,0,1); //Jarra disponible al inicio
    //Todos los palillos estan disponibles al inicio
    sem_init(&palillo1,0,1);
    sem_init(&palillo2,0,1);
    sem_init(&palillo3,0,1);
    sem_init(&palillo4,0,1);
    sem_init(&palillo0,0,1);

    /* crear los procesos ligeros*/
    pthread_create(&th_f1,NULL,(void*)Pensar,(void*)1);
    pthread_create(&th_f2,NULL,(void*)Pensar,(void*)2);
    pthread_create(&th_f3,NULL,(void*)Pensar,(void*)3);
    pthread_create(&th_f4,NULL,(void*)Pensar,(void*)4);
    pthread_create(&th_f0,NULL,(void*)Pensar,(void*)0);

    /*esperar su finalizacion*/
    pthread_join(th_f1,NULL);
    pthread_join(th_f2,NULL);
    pthread_join(th_f3,NULL);
    pthread_join(th_f4,NULL);
    pthread_join(th_f0,NULL);

    sem_destroy(&jarra);
    sem_destroy(&palillo1);
    sem_destroy(&palillo2);
    sem_destroy(&palillo3);
    sem_destroy(&palillo4);
    sem_destroy(&palillo0);
    
    exit(0);
}

void Beber(void *a){
    printf("\nEl filosofo %i: %li quiere beber\n",(int *)a,pthread_self());
    sem_wait(&jarra); //Jarra ocupada
    int drink = 2+rand()%5;
    sleep(drink); //Tiempo para beber
    sem_post(&jarra); //Jarra disponible
    printf("\nEl filosofo %i: %li termino de beber en %d seg\n",(int *)a,pthread_self(),drink);
    Pensar(a); //Cuando termina de beber, se va a pensar
}

void Comer(void *a){
    printf("\nEl filosofo %i: %li quiere comer\n",(int *)a,pthread_self());
    int x=(int *)a; //Para revisar el numero del filosofo

    if(x==0){
        if(sema[4]==1&&sema[0]==1){
            printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
            sem_wait(&palillo0);
            sema[0]=0;
            sem_wait(&palillo4);
            sema[4]=0;
            int eat = 4+rand()%5;
            sleep(eat);
            sem_post(&palillo0);
            sema[0]=1;
            sem_post(&palillo4);
            sema[4]=1;
            printf("\nEl filosofo %i: %li termino de comer en %d seg. Ahora va a pensar\n",(int *)a,pthread_self(),eat);
            Pensar(a);
        }
        else{
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
    else if(x==4){
        if(sema[3]==1&sema[4]==1){
            printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
            sem_wait(&palillo3);
            sema[3]=0;
            sem_wait(&palillo4);
            sema[4]=0;
            int eat = 4+rand()%5;
            sleep(eat);
            sem_post(&palillo3);
            sema[3]=1;
            sem_post(&palillo4);
            sema[4]=1;
            printf("\nEl filosofo %i: %li termino de comer en %d seg. Ahora va a pensar\n",(int *)a,pthread_self(),eat);
            Pensar(a);
        }
        else{
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
    else{
        if(sema[x-1]==1&&sema[x]==1){
            printf("\nEl filosofo %i: %li va a comer\n",(int *)a,pthread_self());
            int eat = 4+rand()%5; //Tiempo para comer
            if(x==1){
                sem_wait(&palillo0);
                sema[0]=0;
                sem_wait(&palillo1);
                sema[1]=0;
                int eat = 4+rand()%5;
                sleep(eat);
                sem_post(&palillo0);
                sema[0]=1;
                sem_post(&palillo1);
                sema[1]=1;
            }
            else if(x==2){
                sem_wait(&palillo1);
                sema[1]=0;
                sem_wait(&palillo2);
                sema[2]=0;
                int eat = 4+rand()%5;
                sleep(eat);
                sem_post(&palillo1);
                sema[1]=1;
                sem_post(&palillo2);
                sema[2]=1;
            }
            else{
                sem_wait(&palillo2);
                sema[2]=0;
                sem_wait(&palillo3);
                sema[3]=0;
                sleep(eat);
                sem_post(&palillo2);
                sema[2]=1;
                sem_post(&palillo3);
                sema[3]=1;
            }
            printf("\nEl filosofo %i: %li termino de comer en %d seg. Ahora va a pensar\n",(int *)a,pthread_self(),eat);
            Pensar(a);
        }
        else{
        	//Si el filosofo no puede comer, procede a beber agua
            printf("\nEl filosofo %i: %li no pudo comer! Ahora va a beber\n",(int *)a,pthread_self());
            Beber(a);
        }
    }
}

void Pensar(void *a){
    int time = 5+rand()%20; 
    printf("\nEl filosofo %i: %li esta pensando por %d seg\n",(int *)a,pthread_self(),time);
    sleep(time); //Tiempo para pensar
    int que_hacer = 0 + rand() %2;
    if(que_hacer==0){
        printf("\nEl filosofo %i: %li le dio hambre\n",(int *)a,pthread_self());
        Comer(a); //Despues de pensar, le da hambre y va a comer
    }
    else{
        printf("\nEl filosofo %i: %li le dio sed\n",(int *)a,pthread_self());
        Beber(a);
    }
}